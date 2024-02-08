/////////////////////////////////////////////////////
//
// PdaMsg.h - сообщение посылаемое при помощи PDA
//
/////////////////////////////////////////////////////

#pragma once
#include "alife_space.h"
#include "pda_space.h"

//структура для описания сообщения PDA,
//используется для ведения логов
typedef struct tagSPdaMessage :
	public IMetaClass
{
	DECLARE_METACLASS(tagSPdaMessage)
public:
	EPdaMsg			msg;
	
	//true если мы получали сообщение 
	//и false если мы его посылали
	bool			receive;
	
	//true, если сообщение - вопрос
	//и false, если ответ
	bool			question;
	
	// информаци
	shared_str		info_id;

	//время получения/отправки сообщения
	ALife::_TIME_ID	time;
		
} SPdaMessage;


//информация о контактах персонажей по PDA и во время диалога
struct TALK_CONTACT_DATA :
	public IMetaClass
{
	DECLARE_METACLASS(TALK_CONTACT_DATA)
public:
	TALK_CONTACT_DATA():id(static_cast<u16>(-1)),time(0){};
	TALK_CONTACT_DATA(u16 contact_id, ALife::_TIME_ID contact_time):id(contact_id),time(contact_time){};
	//время контакта
	ALife::_TIME_ID	time;
	//id персонажа с которым говорили
	u16				id;
};

DEFINE_VECTOR(TALK_CONTACT_DATA, TALK_CONTACT_VECTOR, TALK_CONTACT_VECTOR_IT);
