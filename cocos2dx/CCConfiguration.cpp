/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
Copyright (c) 2010      Ricardo Quesada

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "CCConfiguration.h"
#include "ccMacros.h"
#include "ccConfig.h"
#include <string.h>
#include "CCString.h"

using namespace std;
namespace   cocos2d {


CCConfiguration::CCConfiguration(void)
:m_nMaxTextureSize(0) 
, m_nMaxModelviewStackDepth(0)
, m_bSupportsPVRTC(false)
, m_bSupportsNPOT(false)
, m_bSupportsBGRA8888(false)
, m_bSupportsDiscardFramebuffer(false)
, m_bInited(false)
, m_uOSVersion(0)
, m_nMaxSamplesAllowed(0)
, m_pGlExtensions(NULL)
{
}

bool CCConfiguration::init(void)
{
	CCLOG("cocos2d: GL_VENDOR:     %s", glGetString(GL_VENDOR));
	CCLOG("cocos2d: GL_RENDERER:   %s", glGetString(GL_RENDERER));
	CCLOG("cocos2d: GL_VERSION:    %s", glGetString(GL_VERSION));

	m_pGlExtensions = (char *)glGetString(GL_EXTENSIONS);

	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &m_nMaxTextureSize);
	glGetIntegerv(GL_MAX_MODELVIEW_STACK_DEPTH, &m_nMaxModelviewStackDepth);

	m_bSupportsPVRTC = checkForGLExtension("GL_IMG_texture_compression_pvrtc");
	m_bSupportsNPOT = checkForGLExtension("GL_APPLE_texture_2D_limited_npot");
	m_bSupportsBGRA8888 = checkForGLExtension("GL_IMG_texture_format_BGRA888");
	m_bSupportsDiscardFramebuffer = checkForGLExtension("GL_EXT_discard_framebuffer");

	CCLOG("cocos2d: GL_MAX_TEXTURE_SIZE: %d", m_nMaxTextureSize);
	CCLOG("cocos2d: GL_MAX_MODELVIEW_STACK_DEPTH: %d",m_nMaxModelviewStackDepth);
	CCLOG("cocos2d: GL supports PVRTC: %s", (m_bSupportsPVRTC ? "YES" : "NO"));
	CCLOG("cocos2d: GL supports BGRA8888 textures: %s", (m_bSupportsBGRA8888 ? "YES" : "NO"));
	CCLOG("cocos2d: GL supports NPOT textures: %s", (m_bSupportsNPOT ? "YES" : "NO"));
	CCLOG("cocos2d: GL supports discard_framebuffer: %s", (m_bSupportsDiscardFramebuffer ? "YES" : "NO"));
	
#if CC_TEXTURE_NPOT_SUPPORT
	CCLOG("cocos2d: compiled with NPOT support: %s", "YES");
#else
	CCLOG("cocos2d: compiled with NPOT support: %s", "NO");
#endif // CC_TEXTURE_NPOT_SUPPORT 

	
#if CC_TEXTURE_ATLAS_USES_VBO
	CCLOG("cocos2d: compiled with VBO support in TextureAtlas : %s", "YES");
#else
	CCLOG("cocos2d: compiled with VBO support in TextureAtlas : %s", "NO");
#endif // CC_TEXTURE_ATLAS_USES_VBO

	m_pDict = new CCDictionary<std::string, CCObject*>();
	if (m_pDict != NULL)
	{
		m_pDict->autorelease();
	}
	m_pDict->retain();

	return true;
}

CCConfiguration::~CCConfiguration(void)
{
	m_pDict->release();
}

CCGlesVersion CCConfiguration::getGlesVersion()
{
	// To get the Opengl ES version
	std::string strVersion((char *)glGetString(GL_VERSION));
	if ((int)strVersion.find("1.0") != -1)
	{
		return GLES_VER_1_0;
	}
	else if ((int)strVersion.find("1.1") != -1)
	{
		return GLES_VER_1_1;
	}
	else if ((int)strVersion.find("2.0") != -1)
	{
		return GLES_VER_2_0;
	}
#if (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
	return GLES_VER_2_0;
#else


	return GLES_VER_INVALID;
#endif
}

CCConfiguration* CCConfiguration::sharedConfiguration(void)
{
    static CCConfiguration sharedConfiguration;
    if (!sharedConfiguration.m_bInited)
    {
        sharedConfiguration.init();
        sharedConfiguration.m_bInited = true;
    }
    
    return &sharedConfiguration;
}

bool CCConfiguration::checkForGLExtension(const string &searchName)
{
	bool bRet = false;
	const char *kSearchName = searchName.c_str();
	
	if (m_pGlExtensions && 
		strstr(m_pGlExtensions, kSearchName))
	{
		bRet = true;
	}
	
	return bRet;
}

const char* CCConfiguration::valueForKey(const char *key, CCDictionary<std::string, CCObject*> *dict)
{
	if (dict)
	{
		CCString *pString = (CCString*)dict->objectForKey(std::string(key));
		return pString ? pString->m_sString.c_str() : "";
	}
	return "";
}


const char *CCConfiguration::getCString(const char *key, const char *default_value) const
{
	CCObject *object = m_pDict->objectForKey(key);
	if (object) {
		if ( CCString *str = dynamic_cast<CCString*>(object) )
			return str->m_sString.c_str();

		CCAssert(false, "Key found, but from different type");
	}

	return default_value;
}

bool CCConfiguration::getBool(const char *key, bool default_value/* =false */)
{
	return (atoi(valueForKey(key, m_pDict)) == 0 ? false : true);
}

double CCConfiguration::getNumber(const char *key, double default_value/* =0.0 */)
{
	const char *str = valueForKey(key, m_pDict);
	if (strlen(str) == 0)
		return 0.0;
	else
		return atof(str);
}

CCObject *CCConfiguration::getObject(const char *key) const
{
	return m_pDict->objectForKey(key);
}

void CCConfiguration::setObject(const char *key, CCObject *value)
{
	m_pDict->setObject(value, key);
}

void CCConfiguration::loadConfigFile(const char *filename)
{
	const char *pszPath = CCFileUtils::fullPathFromRelativePath(filename);
	CCDictionary<std::string, CCObject*> *dict = CCFileUtils::dictionaryWithContentsOfFile(pszPath);

	bool metadata_ok = false;
	CCDictionary<std::string, CCObject*> *metadata = (CCDictionary<std::string, CCObject*>*)dict->objectForKey(std::string("metadata"));
	if ( metadata ) {
		int format = atoi(valueForKey("format", metadata));

		if (format == 1) {
			metadata_ok = true;
		}
	}

	if (!metadata_ok)
	{
		CCLOG("Invalid config format for file: %s", filename);
		return;
	}

	CCDictionary<std::string, CCObject*> *data = (CCDictionary<std::string, CCObject*>*)dict->objectForKey(std::string("data"));
	if (!data) {
		CCLOG("Expected 'data' dict, but not found. Config file: %s", filename);
		return;
	}

	data->begin();
	std::string key = "";

	CCDictionary<std::string, CCObject*> *sub_data = NULL;
	while ( (sub_data = (CCDictionary<std::string, CCObject*>*)data->next(&key)) )
	{
		//CCString *pString = (CCString*)sub_data;
		//std::string tmp = pString->m_sString;

		if ( ! m_pDict->objectForKey(key) )
			m_pDict->setObject(sub_data, key);
		else
			CCLOG("Key already present. Ignoring '%s'", key);
	}

}

}//namespace   cocos2d 
