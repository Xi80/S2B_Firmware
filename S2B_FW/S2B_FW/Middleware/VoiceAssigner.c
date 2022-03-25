/*
 * VoiceAssigner.c
 *
 * Created: 2022/03/24 10:00:24
 *  Author: Owner
 */ 

#include "VoiceAssigner.h"

voice_param_t voices[18];

uint8_t voiceCount[16];

uint8_t sustainFlag[16];

void VA_Init(void){
	for(uint8_t i = 0;i < 18;i++){
		voices[i].assign_map = 0x0000;	/*全チャネルに対して割り当て可能*/
		voices[i].assigned_ch = 0xFF;	/*どこにも割り当てない*/
		voices[i].note_number = 0xFF;
		voices[i].note_state  = 0x00;	/*ノートオフ*/
		voices[i].priority    = 0x00;
		voices[i].sustain     = 0x00;
	}

	for(uint8_t i = 12;i < 18;i++){
		voices[i].assign_map = 0x0000;
	}
}

uint8_t VA_AssignOn(uint8_t ch,uint8_t note){
	uint8_t min_prio = 30;
	uint8_t min_vo   = 30;
	
	voiceCount[ch] = 0;
	for(uint8_t i = 0;i < 18;i++){
		if((voices[i].assign_map & (1 << ch)) && !voices[i].note_state){
			/*そのチャネルに対して割り当て可能*/
			if(voices[i].priority <= min_prio){
				/*より優先順位が高い*/
				min_prio = voices[i].priority;
				min_vo   = i;
			}
		}
		if(voices[i].assigned_ch == ch)voiceCount[ch]++;
	}
	if(min_vo == 30)return 255;	//空きがない
	
	/*ノートオン処理*/
	voices[min_vo].assigned_ch = ch;
	voices[min_vo].note_number = note;
	voices[min_vo].note_state = 1;
	voices[min_vo].priority = voiceCount[ch];
	voices[min_vo].sustain = sustainFlag[ch];
	for(uint8_t i = 0; i < 16;i++){
		if(voices[i].assigned_ch == ch){
			voices[i].priority -= (voices[i].priority)? 1 : 0;
		}
	}

	return min_vo;
}

uint8_t VA_AssignOff(uint8_t ch,uint8_t note){
	uint8_t off_count = 0;
	uint8_t off_prio  = 0;
	uint8_t off_vo    = 30;
	
	for(uint8_t i = 0;i < 18;i++){
		if((voices[i].assign_map & (1 << ch))){
			if(!voices[i].note_state)off_count++;
		}
		
		if(voices[i].assigned_ch == ch && voices[i].note_number == note && voices[i].note_state){
			off_prio = voices[i].priority;
			off_vo = i;
		}
	}
	 
	if(off_vo == 30)return 255;
	/*ノートオフ処理*/

	if(!voices[off_vo].sustain)voices[off_vo].assigned_ch = 19;else voices[off_vo].priority = 0;
	voices[off_vo].note_state = 0;
	voices[off_vo].priority = off_count;
	for(uint8_t i = 0;i < 18;i++){
		if((voices[i].assigned_ch == ch ) && voices[i].note_state){
			if(voices[i].note_state){
				voices[i].priority += (voices[i].priority < off_prio)? 1 : 0;
			}
		}
	}
	
	if(voices[off_vo].sustain)return 255;

	return off_vo;
}

struct NoteList_t VA_AssignSustain(uint8_t ch,uint8_t flag){
	struct NoteList_t ret;
	if(flag){
		sustainFlag[ch] = 1;
		for(uint8_t i = 0;i < 18;i++){
			if(voices[i].assigned_ch == ch && voices[i].note_state){
				voices[i].sustain = 1;
			}
		}
		ret.count = 0;
		return ret;
	} else {
		sustainFlag[ch] = 0;
		//ノートオフの処理いろいろ
		ret.count = 0;
		for(uint8_t i = 0;i < 18;i++){
			if(!voices[i].note_state && voices[i].sustain && voices[i].assigned_ch == ch){
				ret.noteId[ret.count++] = i;
			}
			if(voices[i].sustain){
				voices[i].sustain = 0;
			}
		}
		return ret;
	}
}

struct NoteList_t VA_SearchVoices(uint8_t ch){
	struct NoteList_t ret;
	ret.count = 0;
	for(uint8_t i = 0;i < 18;i++){
		if(voices[i].assigned_ch == ch){
			ret.noteNumber[ret.count] = voices[i].note_number;
			ret.noteId[ret.count++] = i;
		}
	}
	return ret;
}

struct NoteList_t VA_GetAssignMap(uint8_t ch){
	struct NoteList_t ret;
	ret.count = 0;
	for(uint8_t i = 0;i < 18;i++){
		if(voices[i].assign_map & (1 << ch)){
			ret.noteId[ret.count++] = i;
		}
	}
	return ret;
}

void VA_SetAssignMap(uint8_t ch,uint8_t count,uint8_t *voice){
	for(uint8_t i = 0;i < 18;i++){
		for(uint8_t j = 0;j < count;j++){
			if(voice[j] == i){
				voices[i].assign_map |= (1 << ch);
				break;
			} else {
				voices[i].assign_map &= ~(1 << ch);
			}
		}
		xprintf("%02x %04x\n",i,voices[i].assign_map);
	}
}