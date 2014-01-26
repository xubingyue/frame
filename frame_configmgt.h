/*
 * frame_configmgt.h
 *
 *  Created on: 2014年1月22日
 *      Author: jimm
 */

#ifndef FRAME_CONFIGMGT_H_
#define FRAME_CONFIGMGT_H_

#include "../common/common_object.h"
#include "../common/common_singleton.h"
#include "frame_impl.h"
#include "frame_namespace.h"

#include <string>
using namespace std;

FRAME_NAMESPACE_BEGIN

class ConfigInfo
{
public:
	ConfigInfo()
	{
		m_pConfig = NULL;
	}
	string		m_strConfigName;
	IConfig		*m_pConfig;
};

class CFrameConfigMgt : public CObject
{
	enum
	{
		enmMaxConfigInfoSize	= 32,	//最大的配置文件数量
	};
public:
	CFrameConfigMgt()
	{
		m_nConfigCount = 0;
	}

	virtual int32_t Init();
	virtual int32_t Uninit();

	void RegistConfig(const char *szConfigName, IConfig *pConfig);

	IConfig *GetConfig(const char *szConfigName);

protected:
	int32_t			m_nConfigCount;
	ConfigInfo		m_arrConfigInfo[enmMaxConfigInfoSize];
};

#define g_FrameConfigMgt		CSingleton<CFrameConfigMgt>::GetInstance()

class regist
{
public:
	regist(const char *szConfigName, IConfig *pConfig)
	{
		g_FrameConfigMgt.RegistConfig(szConfigName, pConfig);
	}
};

#define REGIST_CONFIG(config_name, config_class)	\
	static regist reg_##config_class(config_name, new config_class(config_name))


FRAME_NAMESPACE_END

#endif /* FRAME_CONFIGMGT_H_ */
