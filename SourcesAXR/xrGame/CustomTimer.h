#pragma once

#include <functional>

class CCustomTimerBase
{
protected:
	int             m_iTimerStartValue;
    int             m_iTimerCurValue;
    int             m_iTimerMode; //0 - milliseconds, 1 - seconds, 2 - minutes, 3 hours
    u32             m_iStartTime;

    CCustomTimerBase(const CCustomTimerBase&) = delete;
    CCustomTimerBase& operator=(const CCustomTimerBase&) = delete;

    bool            m_bIsActive;

    virtual void OnTimerEnd() = 0;

public:
    CCustomTimerBase();
    CCustomTimerBase(int value, int mode = 0) : m_iTimerStartValue(value), m_iTimerMode(mode), m_iTimerCurValue(0), m_iStartTime(0), m_bIsActive(false) {}

    ~CCustomTimerBase();

	virtual void StartCustomTimer   ();
    virtual void StopCustomTimer    ();
    virtual void ResetCustomTimer   ();
    void Update             ();

    void setValue           (int value)         {m_iTimerStartValue = value;}
    int  getValue           () const            {return m_iTimerStartValue;}

    void setCurValue        (int value)         {m_iTimerCurValue = value;}
    int  getCurValue        () const            {return m_iTimerCurValue;}

    void setMode            (int mode)          {m_iTimerMode = mode;}
    int  getMode            () const            {return m_iTimerMode;}

    virtual void save               (NET_Packet& output_packet);
    virtual void load               (IReader& input_packet);
};

class CCustomTimer: public CCustomTimerBase
{
    std::string     m_sTimerName;
    std::function<void(std::string)> OnTimerStop = [](std::string) {};

protected:

    virtual void OnTimerEnd() override;

public:
    CCustomTimer() { m_sTimerName = ""; }
    CCustomTimer(std::string name, int value, int mode = 0) : m_sTimerName(name), CCustomTimerBase(value, mode) {}


    virtual void StartCustomTimer() override;
    virtual void StopCustomTimer() override;
    virtual void ResetCustomTimer() override;

    virtual void save(NET_Packet& output_packet) override;
    virtual void load(IReader& input_packet) override;

    void setName(std::string name) { m_sTimerName = name; }
    std::string getName() const { return m_sTimerName; }

    void SetOnTimerStopCallback(std::function<void(std::string)> callback)
    {
        OnTimerStop = callback;
    }
};

class CBinder : public CCustomTimerBase
{
    std::string     m_sFuncName;
    std::vector<std::string> m_params;
    bool m_expired = false;

protected:
    virtual void OnTimerEnd() override;

public:
    CBinder() { m_sFuncName = ""; }
    CBinder(std::string name, const std::vector<std::string>& params, int value, int mode = 0) : m_sFuncName(name), m_params(params), CCustomTimerBase(value, mode)
    {
        StartCustomTimer();
    }

    virtual void save(NET_Packet& output_packet) override;
    virtual void load(IReader& input_packet) override;

    bool getExpired() const { return m_expired; }

};

class CTimerManager
{
    std::vector<std::shared_ptr<CCustomTimer>> Timers;
    std::function<void(std::string)> OnTimerStop = [](std::string) {};

public:
    void CreateTimer    (std::string name, int value, int mode = 0);
    bool DeleteTimer    (std::string name);
    bool ResetTimer     (std::string name);
    bool StartTimer     (std::string name, int start_time = 0, int mode = 0);
    bool StopTimer      (std::string name);

    int  GetTimerValue  (std::string name) const;

    void save           (NET_Packet& output_packet);
    void load           (IReader& input_packet);

    void Update         ();

    void SetOnTimerStopCallback(std::function<void(std::string)> callback)
    {
        OnTimerStop = callback;
    }
};

class CBinderManager
{
    std::vector<std::unique_ptr<CBinder>> Binders;

public:
    void CreateBinder(std::string name, const std::vector<std::string>& params, int value, int mode = 0);

    void save(NET_Packet& output_packet);
    void load(IReader& input_packet);

    void Update();
};

