#pragma once
#ifndef ATLAS_H_
#define ATLAS_H_

#include <vector>
#include <graphics.h>

/*
Atlas 类的作用是用来封装一系列的图集资源，不包含对图集的操作，只涉及对图集加载的IO操作
*/

class Atlas {

public:
	Atlas() = default;
	~Atlas() = default;

	void load_atlas_resource(LPCTSTR file_path_format, int frame_number) {

		image_list.clear();
		image_list.resize(frame_number);

		TCHAR file_path[256];
		for (int i = 0; i < frame_number; i++) {
			_stprintf_s(file_path, file_path_format, i + 1);
			loadimage(&image_list[i], file_path);
		}
	}

	void clear() {
		image_list.clear();
	}

	int get_frame_size() {
		return (int)image_list.size();
	}

	IMAGE* get_image(int index) {
		if (index > image_list.size() || index < 0) {
			return nullptr;
		}
		return &image_list[index];
	}

	void add_image(const IMAGE& img) {
		image_list.push_back(img);
	}

private:
	std::vector<IMAGE> image_list;

};
#endif // !ATLAS_H_
