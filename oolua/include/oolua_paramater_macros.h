///////////////////////////////////////////////////////////////////////////////
///  @file oolua_paramater_macros.h
///  @remarks Warning this file was generated, edits to it will not persist if 
///  the file is regenerated.
///  @author Liam Devine
///  @email
///  See http://www.liamdevine.co.uk for contact details.
///  @licence 
///  See licence.txt for more details. \n 
///////////////////////////////////////////////////////////////////////////////
#ifndef OOLUA_PARAMETER_MACROS_H_
#	define OOLUA_PARAMETER_MACROS_H_

#	include "oolua_config.h"
//param return macros
#define OOLUA_BACK_INTERNAL_(NUM)\
MSC_PUSH_DISABLE_CONDITIONAL_CONSTANT_OOLUA \
	if( P ## NUM ## _::out )\
		OOLUA::INTERNAL::Member_func_helper<P ## NUM ##_,P ## NUM ##_::owner>::push2lua(l,p ## NUM);\
MSC_POP_COMPILER_WARNING_OOLUA


#define OOLUA_BACK_INTERNAL_1\
	OOLUA_BACK_INTERNAL_(1);

#define OOLUA_BACK_INTERNAL_2\
	OOLUA_BACK_INTERNAL_1\
	OOLUA_BACK_INTERNAL_(2);

#define OOLUA_BACK_INTERNAL_3\
	OOLUA_BACK_INTERNAL_2\
	OOLUA_BACK_INTERNAL_(3);

#define OOLUA_BACK_INTERNAL_4\
	OOLUA_BACK_INTERNAL_3\
	OOLUA_BACK_INTERNAL_(4);

#define OOLUA_BACK_INTERNAL_5\
	OOLUA_BACK_INTERNAL_4\
	OOLUA_BACK_INTERNAL_(5);

#define OOLUA_BACK_INTERNAL_6\
	OOLUA_BACK_INTERNAL_5\
	OOLUA_BACK_INTERNAL_(6);

#define OOLUA_BACK_INTERNAL_7\
	OOLUA_BACK_INTERNAL_6\
	OOLUA_BACK_INTERNAL_(7);

#define OOLUA_BACK_INTERNAL_8\
	OOLUA_BACK_INTERNAL_7\
	OOLUA_BACK_INTERNAL_(8);

#define OOLUA_BACK_INTERNAL_9\
	OOLUA_BACK_INTERNAL_8\
	OOLUA_BACK_INTERNAL_(9);


//param macros
#define OOLUA_INTERNAL_PARAM(NUM,PARAM)\
	typedef OOLUA::INTERNAL::param_type<PARAM > P ## NUM ##_;\
	P ## NUM ##_::pull_type p ## NUM;\
	MSC_PUSH_DISABLE_CONDITIONAL_CONSTANT_OOLUA\
	if( P ## NUM ##_::in )\
		OOLUA::INTERNAL::Member_func_helper<P ## NUM ##_,P ## NUM ##_::owner>::pull2cpp(l,p ## NUM);\
	MSC_POP_COMPILER_WARNING_OOLUA

#define OOLUA_PARAMS_INTERNAL_1(PARAM1)\
	OOLUA_INTERNAL_PARAM(1,PARAM1)

#define OOLUA_PARAMS_INTERNAL_2(PARAM1,PARAM2)\
	OOLUA_INTERNAL_PARAM(2,PARAM2)\
	OOLUA_PARAMS_INTERNAL_1(PARAM1)

#define OOLUA_PARAMS_INTERNAL_3(PARAM1,PARAM2,PARAM3)\
	OOLUA_INTERNAL_PARAM(3,PARAM3)\
	OOLUA_PARAMS_INTERNAL_2(PARAM1,PARAM2)

#define OOLUA_PARAMS_INTERNAL_4(PARAM1,PARAM2,PARAM3,PARAM4)\
	OOLUA_INTERNAL_PARAM(4,PARAM4)\
	OOLUA_PARAMS_INTERNAL_3(PARAM1,PARAM2,PARAM3)

#define OOLUA_PARAMS_INTERNAL_5(PARAM1,PARAM2,PARAM3,PARAM4,PARAM5)\
	OOLUA_INTERNAL_PARAM(5,PARAM5)\
	OOLUA_PARAMS_INTERNAL_4(PARAM1,PARAM2,PARAM3,PARAM4)

#define OOLUA_PARAMS_INTERNAL_6(PARAM1,PARAM2,PARAM3,PARAM4,PARAM5,PARAM6)\
	OOLUA_INTERNAL_PARAM(6,PARAM6)\
	OOLUA_PARAMS_INTERNAL_5(PARAM1,PARAM2,PARAM3,PARAM4,PARAM5)

#define OOLUA_PARAMS_INTERNAL_7(PARAM1,PARAM2,PARAM3,PARAM4,PARAM5,PARAM6,PARAM7)\
	OOLUA_INTERNAL_PARAM(7,PARAM7)\
	OOLUA_PARAMS_INTERNAL_6(PARAM1,PARAM2,PARAM3,PARAM4,PARAM5,PARAM6)

#define OOLUA_PARAMS_INTERNAL_8(PARAM1,PARAM2,PARAM3,PARAM4,PARAM5,PARAM6,PARAM7,PARAM8)\
	OOLUA_INTERNAL_PARAM(8,PARAM8)\
	OOLUA_PARAMS_INTERNAL_7(PARAM1,PARAM2,PARAM3,PARAM4,PARAM5,PARAM6,PARAM7)

#define OOLUA_PARAMS_INTERNAL_9(PARAM1,PARAM2,PARAM3,PARAM4,PARAM5,PARAM6,PARAM7,PARAM8,PARAM9)\
	OOLUA_INTERNAL_PARAM(9,PARAM9)\
	OOLUA_PARAMS_INTERNAL_8(PARAM1,PARAM2,PARAM3,PARAM4,PARAM5,PARAM6,PARAM7,PARAM8)


#endif 
