/*
 * SDLAudioPlayer.cpp
 *
 *  Created on: Aug 18, 2011
 *      Author: 
 */

#include "SDLAudioPlayer.h"
#include <stdio.h>
#include "stdlib.h"
#include "assert.h"
#include "string.h"
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

#define szMusicSuffix "|"

namespace CocosDenshion {

struct AudioSource
{
	Mix_Chunk* pMixFile;
	char pName[64];
	int  nFileID;
};

SDLAudioPlayer* SDLAudioPlayer::sharedPlayer() {
	static SDLAudioPlayer s_SharedPlayer;
	return &s_SharedPlayer;
}

// void ERRCHECKWITHEXIT(FMOD_RESULT result) {
// 	if (result != FMOD_OK) {
// 		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
// //		exit(-1);
// 	}
// }
// 
// bool ERRCHECK(FMOD_RESULT result) {
// 	if (result != FMOD_OK) {
// 		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
// 		return true;
// 	}
// 	return false;
// }

SDLAudioPlayer::SDLAudioPlayer() :
		iSoundChannelCount(0) {
	init();
}

void SDLAudioPlayer::init() {
 	//init
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096)==-1)
	{
		fprintf(stderr, "Mix_OpenAudio: %s\n", Mix_GetError());
		m_bIsInitAudio = false;
		//exit(2);
	}
	else
	{
		m_bIsInitAudio = true;
		fprintf(stderr, "Mix_OpenAudio: Success\n");
	}
	//Mix_AllocateChannels(128);

	m_nCurrentFileID = 0;
	m_nCurrentBackgroundMusicID = -1;

	m_nEffectVolume = (int)(0.7f*128.0f);
	m_nMusicVolume = (int)(0.7f*128.0f);
}

void SDLAudioPlayer::close() {
	init();
	if (m_bIsInitAudio)
		Mix_CloseAudio();
}

SDLAudioPlayer::~SDLAudioPlayer() {

}

AudioSource* SDLAudioPlayer::CheckMusicAlreadyLoad(const char * path)
{
	std::vector<AudioSource*>::iterator iter;
	for(iter = m_pMusicMixerList.begin();iter != m_pMusicMixerList.end();iter++)
	{
		if(!strcmp((*iter)->pName,path))
		{
			printf("%s\n",path);
			return *iter;
		}
	}
	return NULL;
}
bool SDLAudioPlayer::RemoveMusicWithFile(int ID)
{
	std::vector<AudioSource*>::iterator iter;
	for(iter = m_pMusicMixerList.begin();iter != m_pMusicMixerList.end();iter++)
	{
		if((*iter)->nFileID == ID)
		{
			Mix_FreeChunk((*iter)->pMixFile);
			m_pMusicMixerList.erase(iter);
			return true;
		}
	}
	return false;
}
AudioSource* SDLAudioPlayer::GetMusicWithID(int nID)
{
	std::vector<AudioSource*>::iterator iter;
	for(iter = m_pMusicMixerList.begin();iter != m_pMusicMixerList.end();iter++)
	{
		if((*iter)->nFileID == nID)
		{
			return *iter;
		}
	}
	return NULL;
}

// BGM
void SDLAudioPlayer::preloadBackgroundMusic(const char* pszFilePath) {
	if(!m_bIsInitAudio)
		return;

	if(strlen(pszFilePath) > 60)
	{
		printf("=== Error:Sound file name too long!\n");
		return;
	}

	if(CheckMusicAlreadyLoad(pszFilePath) != NULL)
		return;
	printf("Add New Sound\n");
	AudioSource* Source = new AudioSource();
	Source->pMixFile = Mix_LoadWAV(pszFilePath);
	strcpy(Source->pName,pszFilePath);

	if(Source->pMixFile == NULL){
		fprintf(stderr, "Error-Mix_LoadWAV: %s------%s\n", Mix_GetError(),pszFilePath);
		delete Source;
	}

	Source->nFileID = m_nCurrentFileID;
	m_nCurrentFileID++;

	m_pMusicMixerList.push_back(Source);

	printf("===CurrentAudioFile%d\n",m_nCurrentFileID);
}

void SDLAudioPlayer::playBackgroundMusic(const char* pszFilePath, bool bLoop) {
	if(!m_bIsInitAudio)
		return;

	stopBackgroundMusic(false);

	preloadBackgroundMusic(pszFilePath);

	AudioSource *Source;
	Source = CheckMusicAlreadyLoad(pszFilePath);
	if(bLoop)
	{
		Source->nFileID = Mix_PlayChannel(Source->nFileID, Source->pMixFile, -1);
	}
	else
	{
		Source->nFileID = Mix_PlayChannel(Source->nFileID, Source->pMixFile, 0);
	}
	m_nCurrentBackgroundMusicID = Source->nFileID;

	printf("CurrentBackGround ID ---%d\n",Source->nFileID);

	Mix_Volume(Source->nFileID, m_nMusicVolume);
}

void SDLAudioPlayer::stopBackgroundMusic(bool bReleaseData) {
	if (m_nCurrentBackgroundMusicID != -1)
	{
		AudioSource* Source;
		Source = GetMusicWithID(m_nCurrentBackgroundMusicID);
		Mix_HaltChannel(m_nCurrentBackgroundMusicID);
		if(bReleaseData)
		{
			RemoveMusicWithFile(m_nCurrentBackgroundMusicID);
			delete Source;
		}
		m_nCurrentBackgroundMusicID = -1;
	}
}

void SDLAudioPlayer::pauseBackgroundMusic() {
	if(m_nCurrentBackgroundMusicID != -1)
		Mix_HaltChannel(m_nCurrentBackgroundMusicID);

	//
// 	if(m_nCurrentBackgroundMusicID != -1)
// 		Mix_Pause(m_nCurrentBackgroundMusicID);
}

void SDLAudioPlayer::resumeBackgroundMusic() {
	if (m_nCurrentBackgroundMusicID != -1)
	{
		printf("Resume\n");
		AudioSource* Source;
		Source = GetMusicWithID(m_nCurrentBackgroundMusicID);

		stopBackgroundMusic(false);
		Mix_PlayChannel(Source->nFileID, Source->pMixFile, -1);
		m_nCurrentBackgroundMusicID = Source->nFileID;
	}
}

void SDLAudioPlayer::rewindBackgroundMusic() {
// 	if (pBGMChannel == NULL) {
// 		return;
// 	}
// 	pSystem->update();
// 	FMOD_RESULT result = pBGMChannel->setPosition(0, FMOD_TIMEUNIT_MS);
// 	ERRCHECKWITHEXIT(result);
}

bool SDLAudioPlayer::willPlayBackgroundMusic() {
/*	pSystem->update();*/
	return false; //do it according to win
}

bool SDLAudioPlayer::isBackgroundMusicPlaying() {

	return Mix_PlayingMusic();
}

float SDLAudioPlayer::getBackgroundMusicVolume() {
	return (float)m_nMusicVolume / 128.0f;
}

void SDLAudioPlayer::setBackgroundMusicVolume(float volume) {
	m_nMusicVolume = volume*128.0f;

	if(!m_bIsInitAudio)
		return;

	std::vector<AudioSource*>::iterator iter;
	for(iter = m_pMusicMixerList.begin();iter != m_pMusicMixerList.end();iter++)
	{
		//printf("CurrentBackGround ID ---%d\n",(*iter)->nFileID);
		Mix_Volume((*iter)->nFileID, (int)m_nMusicVolume);
	}
}
//~BGM

// for sound effects

bool SDLAudioPlayer::RemoveEffectsWithFile(int ID)
{
	std::vector<AudioSource*>::iterator iter;
	for(iter = m_pEffectMixerList.begin();iter != m_pEffectMixerList.end();iter++)
	{
		if((*iter)->nFileID == ID)
		{
			Mix_FreeChunk((*iter)->pMixFile);
			m_pEffectMixerList.erase(iter);
			return true;
		}
	}
	return false;
}
AudioSource* SDLAudioPlayer::CheckEffectAlreadyLoad(const char * path)
{
	std::vector<AudioSource*>::iterator iter;
	for(iter = m_pEffectMixerList.begin();iter != m_pEffectMixerList.end();iter++)
	{
		if(!strcmp((*iter)->pName,path))
		{
			return *iter;
		}
	}
	return NULL;
}
AudioSource* SDLAudioPlayer::GetEffectWithID(int nID)
{
	std::vector<AudioSource*>::iterator iter;
	for(iter = m_pEffectMixerList.begin();iter != m_pEffectMixerList.end();iter++)
	{
		if((*iter)->nFileID == nID)
		{
			return *iter;
		}
	}
	return NULL;
}

float SDLAudioPlayer::getEffectsVolume() {
	return (float)m_nEffectVolume / 128.0f;
}

void SDLAudioPlayer::setEffectsVolume(float volume) {
	Mix_Volume(-1, (int)(volume*128.0f));
}

unsigned int SDLAudioPlayer::playEffect(const char* pszFilePath, bool bLoop) {
	if(!m_bIsInitAudio)
		return 0;

	AudioSource* Source;
	Source = (AudioSource*)preloadEffect(pszFilePath);
	if (!Source)
		return 0;
	
	if(bLoop)
	{
		Source->nFileID = Mix_PlayChannel(-1, Source->pMixFile, -1);
	}
	else
	{
		Source->nFileID = Mix_PlayChannel(-1, Source->pMixFile, 0);
	}
	Mix_Volume(Source->nFileID, m_nEffectVolume);
	return Source->nFileID;
}

void SDLAudioPlayer::stopEffect(unsigned int nSoundId) {

	AudioSource* Source = GetEffectWithID(nSoundId);
	if (Source)
	{
		Mix_HaltChannel(nSoundId);
		RemoveEffectsWithFile(nSoundId);
		delete Source;
	}
}

void SDLAudioPlayer::pauseEffect(unsigned int uSoundId) {
	AudioSource* Source = GetEffectWithID(uSoundId);
	if (Source)
	{
		Mix_Pause(uSoundId);
	}
}

void SDLAudioPlayer::pauseAllEffects() {
	std::vector<AudioSource*>::iterator iter;
	for(iter = m_pEffectMixerList.begin(); iter != m_pEffectMixerList.end(); iter++)
	{
		Mix_Pause((*iter)->nFileID);
	}
}

void SDLAudioPlayer::resumeEffect(unsigned int uSoundId) {
	AudioSource* Source = GetEffectWithID(uSoundId);
	if (Source)
	{
		Mix_Resume(uSoundId);
	}
}

void SDLAudioPlayer::resumeAllEffects() {
	std::vector<AudioSource*>::iterator iter;
	for(iter = m_pEffectMixerList.begin(); iter != m_pEffectMixerList.end(); iter++)
	{
		Mix_Resume((*iter)->nFileID);
	}
}

void SDLAudioPlayer::stopAllEffects() {
	std::vector<AudioSource*>::iterator iter;
	for(iter = m_pEffectMixerList.begin(); iter != m_pEffectMixerList.end(); iter++)
	{
		Mix_HaltChannel((*iter)->nFileID);
		Mix_FreeChunk((*iter)->pMixFile);
		m_pEffectMixerList.erase(iter);
		delete (*iter);
	}
}

void* SDLAudioPlayer::preloadEffect(const char* pszFilePath) {
	if(!m_bIsInitAudio)
		return NULL;

	if(strlen(pszFilePath) > 60)
		return NULL;
	AudioSource* Source = CheckEffectAlreadyLoad(pszFilePath);
	if( Source != NULL)
		return Source;

	printf("Add New Sound\n");

	Source = new AudioSource();
	Source->pMixFile = Mix_LoadWAV(pszFilePath);
	strcpy(Source->pName, pszFilePath);
	Source->nFileID = -1;
	if(Source->pMixFile == NULL){
		fprintf(stderr, "Mix_LoadWAV: %s\n", Mix_GetError());
		delete Source;
		//exit(1);
	}
	m_pEffectMixerList.push_back(Source);
	return Source;
}

void SDLAudioPlayer::unloadEffect(const char* pszFilePath) {
// 	FMOD::Sound* pSound;
// 	pSystem->update();
// 
// 	map<string, FMOD::Sound*>::iterator l_it = mapEffectSound.find(
// 			string(pszFilePath));
// 	if (l_it == mapEffectSound.end()) {
// 		//no load  yet
// 		return;
// 	}
// 	pSound = l_it->second;
// 
// 	//release the sound;
// 	pSound->release();
// 
// 	//delete from the map
// 	mapEffectSound.erase(string(pszFilePath));
}

//~for sound effects

} /* namespace CocosDenshion */
