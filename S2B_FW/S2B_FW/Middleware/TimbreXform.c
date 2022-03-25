/*
 * TimbreXform->c
 *
 * Created: 2022/03/24 18:53:16
 *  Author: Owner
 */ 

#include "TimbreXform.h"

void TX_XformToStruct(struct FMParam_t *to,uint8_t *timbre){
	struct FMParam_t ret;
	ret.al    = timbre[0];
	ret.fb    = timbre[1];
	ret.ar[0] = timbre[2];
	ret.ar[1] = timbre[11];
	ret.ar[2] = timbre[20];
	ret.ar[3] = timbre[29];

	ret.dr[0] = timbre[3];
	ret.dr[1] = timbre[12];
	ret.dr[2] = timbre[21];
	ret.dr[3] = timbre[30];

	ret.sr[0] = timbre[4];
	ret.sr[1] = timbre[13];
	ret.sr[2] = timbre[22];
	ret.sr[3] = timbre[31];

	ret.rr[0] = timbre[5];
	ret.rr[1] = timbre[14];
	ret.rr[2] = timbre[23];
	ret.rr[3] = timbre[32];

	ret.sl[0] = timbre[6];
	ret.sl[1] = timbre[15];
	ret.sl[2] = timbre[24];
	ret.sl[3] = timbre[33];

	ret.tl[0] = timbre[7];
	ret.tl[1] = timbre[16];
	ret.tl[2] = timbre[25];
	ret.tl[3] = timbre[34];

	ret.ks[0] = timbre[8];
	ret.ks[1] = timbre[17];
	ret.ks[2] = timbre[25];
	ret.ks[3] = timbre[34];

	ret.ml[0] = timbre[9];
	ret.ml[1] = timbre[18];
	ret.ml[2] = timbre[27];
	ret.ml[3] = timbre[36];

	ret.dt[0] = timbre[10];
	ret.dt[1] = timbre[19];
	ret.dt[2] = timbre[28];
	ret.dt[3] = timbre[37];

	memcpy(&to,&ret,sizeof(ret));
}

void TX_XformToArray(uint8_t *to,struct FMParam_t *timbre){
	uint8_t ret[38];
	ret[0]   = timbre->al;
	ret[1]	= timbre->fb;
	ret[2]	= timbre->ar[0] ;
	ret[11]	= timbre->ar[1] ;
	ret[20]	= timbre->ar[2] ;
	ret[29]	= timbre->ar[3] ;

	ret[3]	= timbre->dr[0] ;
	ret[12]	= timbre->dr[1] ;
	ret[21]	= timbre->dr[2] ;
	ret[30]	= timbre->dr[3] ;

	ret[4]	= timbre->sr[0] ;
	ret[13]	= timbre->sr[1] ;
	ret[22]	= timbre->sr[2] ;
	ret[31]	= timbre->sr[3] ;

	ret[5]	= timbre->rr[0] ;
	ret[14]	= timbre->rr[1] ;
	ret[23]	= timbre->rr[2] ;
	ret[32]	= timbre->rr[3] ;

	ret[6]	= timbre->sl[0] ;
	ret[15]	= timbre->sl[1] ;
	ret[24]	= timbre->sl[2] ;
	ret[33]	= timbre->sl[3] ;

	ret[7]	= timbre->tl[0] ;
	ret[16]	= timbre->tl[1] ;
	ret[25]	= timbre->tl[2] ;
	ret[34]	= timbre->tl[3] ;

	ret[8]	= timbre->ks[0] ;
	ret[17]	= timbre->ks[1] ;
	ret[25]	= timbre->ks[2] ;
	ret[34]	= timbre->ks[3] ;

	ret[9]	= timbre->ml[0] ;
	ret[18]	= timbre->ml[1] ;
	ret[27]	= timbre->ml[2] ;
	ret[36]	= timbre->ml[3] ;

	ret[10]	= timbre->dt[0] ;
	ret[19]	= timbre->dt[1] ;
	ret[28]	= timbre->dt[2] ;
	ret[37]	= timbre->dt[3] ;

	memcpy(to,ret,38);
}