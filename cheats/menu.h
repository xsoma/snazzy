#pragma once
#include "../includes.hpp"

class qgui : public singleton<qgui> {
public:
	void init_styles(ImGuiStyle& style, LPDIRECT3DDEVICE9 device);
	void shadow(ImDrawList* drawlist, ImVec2 pos, ImVec2 size, ImVec4 color);
	void render_decorations();
	void render_tabs();
	void render_content();
	void render_menu(bool is_open);

	float dpi_scale = 1.f;

	ImFont* futura;
	ImFont* futura_large;
	ImFont* icons;
	ImFont* bigxd;
	ImFont* futura_small;
	ImFont* snazzyfont;
	//vgui::HFont snazzyfont;

	ImFont* gotham;

	ImFont* ico_menu;
	ImFont* ico_bottom;

	float public_alpha;
	IDirect3DDevice9* device;
	float color_buffer[4] = { 1.f, 1.f, 1.f, 1.f };
private:
	struct {
		ImVec2 WindowPadding;
		float  WindowRounding;
		ImVec2 WindowMinSize;
		float  ChildRounding;
		float  PopupRounding;
		ImVec2 FramePadding;
		float  FrameRounding;
		ImVec2 ItemSpacing;
		ImVec2 ItemInnerSpacing;
		ImVec2 TouchExtraPadding;
		float  IndentSpacing;
		float  ColumnsMinSpacing;
		float  ScrollbarSize;
		float  ScrollbarRounding;
		float  GrabMinSize;
		float  GrabRounding;
		float  TabRounding;
		float  TabMinWidthForUnselectedCloseButton;
		ImVec2 DisplayWindowPadding;
		ImVec2 DisplaySafeAreaPadding;
		float  MouseCursorScale;
	} styles;

	bool update_dpi = false;
	void dpi_resize(float scale_factor, ImGuiStyle &style);

	int active_tab_index;
	ImGuiStyle style;
	int width = 850, height = 560;
	float child_height;

	float preview_alpha = 1.f;

	int active_tab;

	int rage_section;
	int legit_section;
	int visuals_section;
	int players_section;
	int misc_section;
	int settings_section;

	// we need to use 'int child' to seperate content in 2 childs


	ImGuiStyle        _style;
	 

	int current_profile = -1;


	std::string preview = crypt_str("None");
};
