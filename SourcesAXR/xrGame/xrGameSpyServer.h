#pragma once

#include "xrServer.h"
#include "GameSpy/GameSpy_GCD_Server.h"
#include "GameSpy/GameSpy_QR2.h"


class xrGameSpyClientData	: public xrClientData
{
private:
	typedef xrClientData inherited;
public:
	string64			m_pChallengeString;
	int					m_iCDKeyReauthHint;
	bool				m_bCDKeyAuth;

	xrGameSpyClientData			();
	void				Clear() override;
	~xrGameSpyClientData	() override;
};

class xrGameSpyServer	: public xrServer
{
private:
	typedef xrServer inherited;

	enum
	{
		server_flag_password	= static_cast<u8>(1 << 0),
		server_flag_protected	= static_cast<u8>(1 << 1),
		server_flag_2	= static_cast<u8>(1 << 2),
		server_flag_3	= static_cast<u8>(1 << 3),
		server_flag_4	= static_cast<u8>(1 << 4),
		server_flag_5	= static_cast<u8>(1 << 5),
		server_flag_6	= static_cast<u8>(1 << 6),
		server_flag_128	= static_cast<u8>(1 << 7),
		server_flag_all	= static_cast<u8>(-1)
	};

private:
	int								m_iReportToMasterServer;

	BOOL							m_bQR2_Initialized;
	void							QR2_Init						(int PortID);
	void							QR2_ShutDown					();
	
	BOOL							m_bCDKey_Initialized;
	void							CDKey_Init						();
	void							CDKey_ShutDown					();
	void							SendChallengeString_2_Client	(IClient* C);
	
	CGameSpy_GCD_Server				m_GCDServer;
	CGameSpy_QR2					m_QR2;
	int							iGameSpyBasePort;

protected:
	bool					NeedToCheckClient_GameSpy_CDKey	(IClient* CL) override;
	bool				Check_ServerAccess( IClient* CL, string512& reason ) override;

public:
	shared_str						HostName;
	shared_str						MapName;
	shared_str						Password;
	Flags8						ServerFlags;

	int								m_iMaxPlayers;
	bool							m_bCheckCDKey;
	

	int								GetPlayersCount					();
	void							OnCDKey_Validation				(int LocalID, int res, char* errormsg);
	void							OnCDKey_ReValidation			(int LocalID, int hint, char* challenge);
	CGameSpy_QR2*					QR2() {return &m_QR2;} ;

	CGameSpy_GCD_Server*		GCD_Server()					{ return &m_GCDServer; }

	bool				HasPassword() override;
	bool				HasProtected() override;

	void				Assign_ServerType( string512& res ) override;
	void				GetServerInfo( CServerInfo* si ) override;
			bool				IsPublicServer() const { return m_iReportToMasterServer != 0; };

public:
	xrGameSpyServer					();
	~xrGameSpyServer		() override;

	EConnect		Connect				(shared_str& session_name, GameDescriptionData & game_descr) override;
	void			Update				() override;

//	virtual void			OnCL_Connected		(IClient* C);
	void			OnCL_Disconnected	(IClient* C) override;
	IClient*		client_Create		() override;

	u32				OnMessage			(NET_Packet& P, ClientID/*DPNID*/ sender) override;	// Non-Zero means broadcasting with "flags" as returned
	virtual void			OnError_Add			(qr2_error_t error) {};
};

