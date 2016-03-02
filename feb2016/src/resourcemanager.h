#ifndef __RESOURCE_MANAGER_H
#define __RESOURCE_MANAGER_H

#include "surface.h"
#include "font.h"

class ResourceManager
{
public:
	static ResourceManager *get_instance();
	~ResourceManager();

	Surface *get_image(const char *filename);
	void play_sound(const char *filename);
	void play_music(const char *filename);
	void stop_music(int delay = 0);

	Font *get_font();
private:
	ResourceManager();
	static ResourceManager *m_instance;

	map<string, Surface *> m_images;
	map<string, Mix_Chunk *> m_chunk;
	map<string, Mix_Music *> m_music;
	string m_cur_music;
	Font *m_font;
};

#endif
