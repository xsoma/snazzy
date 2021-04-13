#pragma once



#include "..\..\includes.hpp"







struct some_add {

	int ent_index;
	ModelRenderInfo_t	 info;
	DrawModelState_t	 state;
	matrix3x4_t			 pBoneToWorld[128] = {};
	float				 time;
	matrix3x4_t			 model_to_world;

};

inline std::vector<some_add> m_Hitmatrix;


class hit_chams
{
public:
	void add_matrix(player_t* player, matrix3x4_t* bones);
	void draw_hit_matrix();
};

inline hit_chams chams_on_hit;

