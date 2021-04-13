/////////////////////////////////////////////////////
//                                                   
//    Generated with QuarcStudio. (ex. ImGui Editor) 
//    QuarcStudio is designed with love by pers0na2. 
//    All rights to QuarcStudio belong to pers0na2.  
//                                                   
/////////////////////////////////////////////////////




#include <string>

#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

#include "../ImGui/imgui.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#define IM_USE using namespace ImGui; 
#include "../ImGui/imgui_internal.h"

#include "../New menu shit/sffont.hpp"
#include "../New menu shit/hashes.h"
#include "../New menu shit/faprolight.hpp"

#include <vector>

#include "../New menu shit/zcraw.h"
#include "../New menu shit/Vector.hpp"
#include "menu.h"

#include "../constchars.h"
#include <any>
#include "../nSkinz/SkinChanger.h"
#include "../nSkinz/item_definitions.hpp"
#include "../nSkinz/Utilities/Platform.hpp"
#include "../nSkinz/Utilities/vmt_smart_hook.hpp"
#include "misc/logs.h"
#include <ShlObj_core.h>
#include "../SnazzyIcons.h"

#define ALPHA (ImGuiColorEditFlags_AlphaPreview | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaBar| ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_Float)
#define NOALPHA (ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_Float)

std::vector <std::string> files;

static auto menu_setupped = false;
static auto should_update = true;

IDirect3DTexture9* all_skins[36];

std::string get_wep(int id, int custom_index = -1, bool knife = true)
{
	if (custom_index > -1)
	{
		if (knife)
		{
			switch (custom_index)
			{
			case 0: return crypt_str("weapon_knife");
			case 1: return crypt_str("weapon_bayonet");
			case 2: return crypt_str("weapon_knife_css");
			case 3: return crypt_str("weapon_knife_skeleton");
			case 4: return crypt_str("weapon_knife_outdoor");
			case 5: return crypt_str("weapon_knife_cord");
			case 6: return crypt_str("weapon_knife_canis");
			case 7: return crypt_str("weapon_knife_flip");
			case 8: return crypt_str("weapon_knife_gut");
			case 9: return crypt_str("weapon_knife_karambit");
			case 10: return crypt_str("weapon_knife_m9_bayonet");
			case 11: return crypt_str("weapon_knife_tactical");
			case 12: return crypt_str("weapon_knife_falchion");
			case 13: return crypt_str("weapon_knife_survival_bowie");
			case 14: return crypt_str("weapon_knife_butterfly");
			case 15: return crypt_str("weapon_knife_push");
			case 16: return crypt_str("weapon_knife_ursus");
			case 17: return crypt_str("weapon_knife_gypsy_jackknife");
			case 18: return crypt_str("weapon_knife_stiletto");
			case 19: return crypt_str("weapon_knife_widowmaker");
			}
		}
		else
		{
			switch (custom_index)
			{
			case 0: return crypt_str("ct_gloves"); //-V1037
			case 1: return crypt_str("studded_bloodhound_gloves");
			case 2: return crypt_str("t_gloves");
			case 3: return crypt_str("ct_gloves");
			case 4: return crypt_str("sporty_gloves");
			case 5: return crypt_str("slick_gloves");
			case 6: return crypt_str("leather_handwraps");
			case 7: return crypt_str("motorcycle_gloves");
			case 8: return crypt_str("specialist_gloves");
			case 9: return crypt_str("studded_hydra_gloves");
			}
		}
	}
	else
	{
		switch (id)
		{
		case 0: return crypt_str("knife");
		case 1: return crypt_str("gloves");
		case 2: return crypt_str("weapon_ak47");
		case 3: return crypt_str("weapon_aug");
		case 4: return crypt_str("weapon_awp");
		case 5: return crypt_str("weapon_cz75a");
		case 6: return crypt_str("weapon_deagle");
		case 7: return crypt_str("weapon_elite");
		case 8: return crypt_str("weapon_famas");
		case 9: return crypt_str("weapon_fiveseven");
		case 10: return crypt_str("weapon_g3sg1");
		case 11: return crypt_str("weapon_galilar");
		case 12: return crypt_str("weapon_glock");
		case 13: return crypt_str("weapon_m249");
		case 14: return crypt_str("weapon_m4a1_silencer");
		case 15: return crypt_str("weapon_m4a1");
		case 16: return crypt_str("weapon_mac10");
		case 17: return crypt_str("weapon_mag7");
		case 18: return crypt_str("weapon_mp5sd");
		case 19: return crypt_str("weapon_mp7");
		case 20: return crypt_str("weapon_mp9");
		case 21: return crypt_str("weapon_negev");
		case 22: return crypt_str("weapon_nova");
		case 23: return crypt_str("weapon_hkp2000");
		case 24: return crypt_str("weapon_p250");
		case 25: return crypt_str("weapon_p90");
		case 26: return crypt_str("weapon_bizon");
		case 27: return crypt_str("weapon_revolver");
		case 28: return crypt_str("weapon_sawedoff");
		case 29: return crypt_str("weapon_scar20");
		case 30: return crypt_str("weapon_ssg08");
		case 31: return crypt_str("weapon_sg556");
		case 32: return crypt_str("weapon_tec9");
		case 33: return crypt_str("weapon_ump45");
		case 34: return crypt_str("weapon_usp_silencer");
		case 35: return crypt_str("weapon_xm1014");
		default: return crypt_str("unknown");
		}
	}
}

IDirect3DTexture9* get_skin_preview(const char* weapon_name, const std::string& skin_name, IDirect3DDevice9* device)
{
	IDirect3DTexture9* skin_image = nullptr;
	std::string vpk_path;

	if (strcmp(weapon_name, crypt_str("unknown")) && strcmp(weapon_name, crypt_str("knife")) && strcmp(weapon_name, crypt_str("gloves"))) //-V526
	{
		if (skin_name.empty() || skin_name == crypt_str("default"))
			vpk_path = crypt_str("resource/flash/econ/weapons/base_weapons/") + std::string(weapon_name) + crypt_str(".png");
		else
			vpk_path = crypt_str("resource/flash/econ/default_generated/") + std::string(weapon_name) + crypt_str("_") + std::string(skin_name) + crypt_str("_light_large.png");
	}
	else
	{
		if (!strcmp(weapon_name, crypt_str("knife")))
			vpk_path = crypt_str("resource/flash/econ/weapons/base_weapons/weapon_knife.png");
		else if (!strcmp(weapon_name, crypt_str("gloves")))
			vpk_path = crypt_str("resource/flash/econ/weapons/base_weapons/ct_gloves.png");
		else if (!strcmp(weapon_name, crypt_str("unknown")))
			vpk_path = crypt_str("resource/flash/econ/weapons/base_weapons/weapon_snowball.png");

	}
	const auto handle = m_basefilesys()->Open(vpk_path.c_str(), crypt_str("r"), crypt_str("GAME"));
	if (handle)
	{
		int file_len = m_basefilesys()->Size(handle);
		char* image = new char[file_len]; //-V121

		m_basefilesys()->Read(image, file_len, handle);
		m_basefilesys()->Close(handle);

		D3DXCreateTextureFromFileInMemory(device, image, file_len, &skin_image);
		delete[] image;
	}

	if (!skin_image)
	{
		std::string vpk_path;

		if (strstr(weapon_name, crypt_str("bloodhound")) != NULL || strstr(weapon_name, crypt_str("hydra")) != NULL)
			vpk_path = crypt_str("resource/flash/econ/weapons/base_weapons/ct_gloves.png");
		else
			vpk_path = crypt_str("resource/flash/econ/weapons/base_weapons/") + std::string(weapon_name) + crypt_str(".png");

		const auto handle = m_basefilesys()->Open(vpk_path.c_str(), crypt_str("r"), crypt_str("GAME"));

		if (handle)
		{
			int file_len = m_basefilesys()->Size(handle);
			char* image = new char[file_len]; //-V121

			m_basefilesys()->Read(image, file_len, handle);
			m_basefilesys()->Close(handle);

			D3DXCreateTextureFromFileInMemory(device, image, file_len, &skin_image);
			delete[] image;
		}
	}

	return skin_image;
}

ImVec2 p;
ImDrawList* draw;
IDirect3DTexture9* background;

float alphamodulate = 0.0f;

static int selectedtab = 1;
static int selectedsubtab = 1;

void qgui::init_styles(ImGuiStyle& style, LPDIRECT3DDEVICE9 device)
{
	style.WindowPadding = ImVec2(0.000000f, 0.000000f);
	style.FramePadding = ImVec2(4.000000f, 3.000000f);
	style.ItemSpacing = ImVec2(8.000000f, 4.000000f);
	style.ItemInnerSpacing = ImVec2(4.000000f, 4.000000f);
	style.IndentSpacing = 21.000000f;
	style.ScrollbarSize = 15.000000f;
	style.GrabMinSize = 1.000000f;
	style.WindowBorderSize = 0.000000f;
	style.ChildBorderSize = 1.000000f;
	style.PopupBorderSize = 0.000000f;
	style.FrameBorderSize = 1.000000f;
	style.WindowRounding = 0.000000f;
	style.ChildRounding = 0.000000f;
	style.FrameRounding = 0.000000f;
	style.PopupRounding = 0.000000f;
	style.ScrollbarRounding = 4.000000f;
	style.GrabRounding = 0.000000f;
	style.WindowTitleAlign = ImVec2(0.000000f, 0.500000f);
	style.ButtonTextAlign = ImVec2(0.500000f, 0.500000f);
	style.SelectableTextAlign = ImVec2(0.500000f, 0.500000f);

	style.Colors[ImGuiCol_Text] = ImVec4(0.900000f, 0.900000f, 0.900000f, 1.000000f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.600000f, 0.600000f, 0.600000f, 1.000000f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.058824f, 0.058824f, 0.058824f, 1.000000f);
	style.Colors[ImGuiCol_ChildBg] = ImVec4(0.000000f, 0.000000f, 0.000000f, 0.000000f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(57 / 255.f, 57 / 255.f, 57 / 255.f, 1);
	style.Colors[ImGuiCol_Border] = ImVec4(0.500000f, 0.500000f, 0.500000f, 0.500000f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.000000f, 0.000000f, 0.000000f, 0.000000f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.430000f, 0.430000f, 0.430000f, 0.390000f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.470000f, 0.470000f, 0.690000f, 0.400000f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.420000f, 0.410000f, 0.640000f, 0.690000f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.270000f, 0.270000f, 0.540000f, 0.830000f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.320000f, 0.320000f, 0.630000f, 0.870000f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.400000f, 0.400000f, 0.800000f, 0.200000f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.400000f, 0.400000f, 0.550000f, 0.800000f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.200000f, 0.250000f, 0.300000f, 0.000000f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.400000f, 0.400000f, 0.400000f, 0.300000f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.400000f, 0.400000f, 0.400000f, 0.400000f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.400000f, 0.400000f, 0.400000f, 0.600000f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.900000f, 0.900000f, 0.900000f, 0.500000f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(1.000000f, 1.000000f, 1.000000f, 0.300000f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.410000f, 0.390000f, 0.800000f, 0.600000f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.350000f, 0.400000f, 0.610000f, 0.620000f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.400000f, 0.480000f, 0.710000f, 0.790000f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.460000f, 0.540000f, 0.800000f, 1.000000f);
	style.Colors[ImGuiCol_Header] = ImVec4(45 / 255.f, 45 / 255.f, 45 / 255.f, 1);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(50 / 255.f, 50 / 255.f, 50 / 255.f, 1);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(45 / 255.f, 45 / 255.f, 45 / 255.f, 1);
	style.Colors[ImGuiCol_Separator] = ImVec4(0.500000f, 0.500000f, 0.500000f, 0.600000f);
	style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.600000f, 0.600000f, 0.700000f, 1.000000f);
	style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.700000f, 0.700000f, 0.900000f, 1.000000f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(1.000000f, 1.000000f, 1.000000f, 0.160000f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.780000f, 0.820000f, 1.000000f, 0.600000f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.780000f, 0.820000f, 1.000000f, 0.900000f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.000000f, 0.000000f, 1.000000f, 0.350000f);
	style.Colors[ImGuiCol_DragDropTarget] = ImVec4(1.000000f, 1.000000f, 0.000000f, 0.900000f);

	static const ImWchar ranges[] =
	{
		0x0020, 0x00FF, // Basic Latin + Latin Supplement
		0x2000, 0x206F, // General Punctuation
		0x3000, 0x30FF, // CJK Symbols and Punctuations, Hiragana, Katakana
		0x31F0, 0x31FF, // Katakana Phonetic Extensions
		0xFF00, 0xFFEF, // Half-width characters
		0x4e00, 0x9FAF, // CJK Ideograms
		0x0400, 0x052F, // Cyrillic + Cyrillic Supplement
		0x2DE0, 0x2DFF, // Cyrillic Extended-A
		0xA640, 0xA69F, // Cyrillic Extended-B
		0,
	};

	/*ImFontConfig font_cfg{};
	font_cfg.FontDataOwnedByAtlas = false;
	ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(sfpro_compressed_data, sfpro_compressed_size, 12, &font_cfg, ranges);

	static const ImWchar icon_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
	ImFontConfig icons_config; icons_config.MergeMode = true; icons_config.PixelSnapH = true;
	ImGui::GetIO().Fonts->AddFontFromMemoryTTF(&faprolight, sizeof faprolight, 16, &icons_config, icon_ranges);*/

	if (background == nullptr)
		D3DXCreateTextureFromFileInMemoryEx(device, &backgroundraw, sizeof(backgroundraw), 845, 560, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &background);
}

std::string get_config_dir()
{
	std::string folder;
	static TCHAR path[MAX_PATH];

	if (SUCCEEDED(SHGetFolderPath(NULL, 0x001a, NULL, NULL, path)))
		folder = std::string(path) + crypt_str("\\Snazzy\\Configs\\");

	CreateDirectory(folder.c_str(), NULL);
	return folder;
}

void load_config()
{
	if (cfg_manager->files.empty())
		return;

	cfg_manager->load(cfg_manager->files.at(g_cfg.selected_config), false);

	for (auto i = 0; i < g_cfg.skins.skinChanger.size(); ++i)
		all_skins[i] = nullptr;

	cfg_manager->load(cfg_manager->files.at(g_cfg.selected_config), true);
	cfg_manager->config_files();

	eventlogs::get().add(("Loaded ") + files.at(g_cfg.selected_config) + (" config"), false);
}

void save_config()
{
	if (cfg_manager->files.empty())
		return;

	cfg_manager->save(cfg_manager->files.at(g_cfg.selected_config));
	cfg_manager->config_files();

	eventlogs::get().add(("Saved ") + files.at(g_cfg.selected_config) + (" config"), false);
}

void remove_config()
{
	if (cfg_manager->files.empty())
		return;

	eventlogs::get().add(("Removed ") + files.at(g_cfg.selected_config) + (" config"), false);

	cfg_manager->remove(cfg_manager->files.at(g_cfg.selected_config));
	cfg_manager->config_files();

	files = cfg_manager->files;

	if (g_cfg.selected_config >= files.size())
		g_cfg.selected_config = files.size() - 1; //-V103

	for (auto& current : files)
		if (current.size() > 2)
			current.erase(current.size() - 3, 3);
}

void add_config()
{
	auto empty = true;

	for (auto current : g_cfg.new_config_name)
	{
		if (current != ' ')
		{
			empty = false;
			break;
		}
	}

	if (empty)
		g_cfg.new_config_name = ("config");

	eventlogs::get().add(("Added ") + g_cfg.new_config_name + (" config"), false);

	if (g_cfg.new_config_name.find(("")) == std::string::npos)
		g_cfg.new_config_name += ("");

	cfg_manager->save(g_cfg.new_config_name);
	cfg_manager->config_files();

	g_cfg.selected_config = cfg_manager->files.size() - 1; //-V103
	files = cfg_manager->files;

	for (auto& current : files)
		if (current.size() > 2)
			current.erase(current.size() - 3, 3);
}

bool checkbox(const char* label, bool* v)
{
	IM_USE;
	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);
	const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);
	const float square_sz = ImGui::GetFrameHeight();
	const ImVec2 pos = window->DC.CursorPos;
	const ImRect total_bb(pos + ImVec2(10, 5), pos + ImVec2(square_sz + (style.ItemInnerSpacing.x + label_size.x + 0), 0 + label_size.y + style.FramePadding.y * 2) + ImVec2(10, 5));
	ItemSize(total_bb, style.FramePadding.y);
	ItemAdd(total_bb, id);

	bool hovered, held;
	bool pressed = ButtonBehavior(total_bb, id, &hovered, &held);

	if (hovered || held)
		ImGui::SetMouseCursor(7);

	if (pressed)
		*v = !(*v);

	window->DrawList->AddRectFilled(ImVec2(total_bb.Min.x + 0, total_bb.Min.y + 0), ImVec2(total_bb.Min.x + 10, total_bb.Min.y + 10), ImColor(37, 37, 37, int(alphamodulate * 253)), 0, 15);
	window->DrawList->AddRect(ImVec2(total_bb.Min.x + 0, total_bb.Min.y + 0), ImVec2(total_bb.Min.x + 10, total_bb.Min.y + 10), ImColor(27, 27, 27, int(alphamodulate * 253)), 0, 15);

	if (*v)
	{
		window->DrawList->AddRectFilledMultiColor(ImVec2(total_bb.Min.x + 1, total_bb.Min.y + 1), ImVec2(total_bb.Min.x + 9, total_bb.Min.y + 9), ImColor(112 / 255.f, 15 / 255.f, 247 / 255.f, alphamodulate), ImColor(112 / 255.f, 15 / 255.f, 247 / 255.f, alphamodulate), ImColor(0, 54, 116, int(alphamodulate * 253)), ImColor(0, 54, 116, int(alphamodulate * 253)));
	}

	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(214 / 255.f, 214 / 255.f, 214 / 255.f, alphamodulate));
	ImGui::RenderText(ImVec2(total_bb.Min.x + style.ItemInnerSpacing.x + 10, total_bb.Min.y + style.FramePadding.y + -4), label);
	ImGui::PopStyleColor();
	return pressed;
}



void child_title(const char* label)
{
	ImGui::PushFont(qgui::get().futura_large);
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 1.f, 1.f, 1.f));

	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + (12 * qgui::get().dpi_scale));
	ImGui::Text(label);

	ImGui::PopStyleColor();
	ImGui::PopFont();
}

bool beginchildex(const char* name, ImGuiID id, const ImVec2& size_arg, bool border, ImGuiWindowFlags flags)
{
	IM_USE;

	ImGuiContext& g = *GImGui;
	ImGuiWindow* parent_window = g.CurrentWindow;

	flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_ChildWindow;
	flags |= (parent_window->Flags & ImGuiWindowFlags_NoMove);  // Inherit the NoMove flag

	// Size
	const ImVec2 content_avail = GetContentRegionAvail();
	ImVec2 size = ImFloor(size_arg);
	const int auto_fit_axises = ((size.x == 0.0f) ? (1 << ImGuiAxis_X) : 0x00) | ((size.y == 0.0f) ? (1 << ImGuiAxis_Y) : 0x00);
	if (size.x <= 0.0f)
		size.x = ImMax(content_avail.x + size.x, 4.0f); // Arbitrary minimum child size (0.0f causing too much issues)
	if (size.y <= 0.0f)
		size.y = ImMax(content_avail.y + size.y, 4.0f);
	SetNextWindowSize(size);

	// Build up name. If you need to append to a same child from multiple location in the ID stack, use BeginChild(ImGuiID id) with a stable value.
	char title[256];
	if (name)
		ImFormatString(title, IM_ARRAYSIZE(title), "%s/%s_%08X", parent_window->Name, name, id);
	else
		ImFormatString(title, IM_ARRAYSIZE(title), "%s/%08X", parent_window->Name, id);

	const float backup_border_size = g.Style.ChildBorderSize;
	if (!border)
		g.Style.ChildBorderSize = 0.0f;
	bool ret = Begin(title, NULL, flags);
	g.Style.ChildBorderSize = backup_border_size;

	ImGuiWindow* child_window = g.CurrentWindow;
	child_window->ChildId = id;
	child_window->AutoFitChildAxises = (ImS8)auto_fit_axises;

	// Set the cursor to handle case where the user called SetNextWindowPos()+BeginChild() manually.
	// While this is not really documented/defined, it seems that the expected thing to do.
	if (child_window->BeginCount == 1)
		parent_window->DC.CursorPos = child_window->Pos;

	// Process navigation-in immediately so NavInit can run on first frame
	if (g.NavActivateId == id && !(flags & ImGuiWindowFlags_NavFlattened) && (child_window->DC.NavLayerActiveMask != 0 || child_window->DC.NavHasScroll))
	{
		FocusWindow(child_window);
		NavInitWindow(child_window, false);
		SetActiveID(id + 1, child_window); // Steal ActiveId with another arbitrary id so that key-press won't activate child item
		g.ActiveIdSource = ImGuiInputSource_Nav;
	}
	parent_window->DrawList->AddRectFilled(ImGui::GetWindowPos(), ImGui::GetWindowPos() + size_arg, ImColor(12, 12, 12, int(alphamodulate * 170)), 0);
	parent_window->DrawList->AddRect(ImGui::GetWindowPos(), ImGui::GetWindowPos() + size_arg, ImColor(59, 59, 59, int(alphamodulate * 140)), 0);
	parent_window->DrawList->AddRect(ImGui::GetWindowPos() + ImVec2(1, 1), ImGui::GetWindowPos() + size_arg - ImVec2(1, 1), ImColor(2, 2, 2, int(alphamodulate * 170)), 0);
	return ret;
}

bool button(const char* label, const ImVec2& size_arg)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);
	const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

	ImVec2 pos = window->DC.CursorPos + ImVec2(11, 3);
	ImVec2 size = ImGui::CalcItemSize(size_arg, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);

	const ImRect bb(pos, pos + size);
	ImGui::ItemSize(size, style.FramePadding.y);
	if (!ImGui::ItemAdd(bb, id))
		return false;

	bool hovered, held;
	bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, NULL);

	if (hovered || held)
		ImGui::SetMouseCursor(7);

	if (!hovered)
		window->DrawList->AddRectFilledMultiColor(ImVec2(bb.Min.x, bb.Min.y), ImVec2(bb.Max.x, bb.Max.y), ImColor(51, 51, 51, int(alphamodulate * 253)), ImColor(51, 51, 51, int(alphamodulate * 253)), ImColor(39, 39, 40, int(alphamodulate * 253)), ImColor(39, 39, 40, int(alphamodulate * 253)));
	else
		window->DrawList->AddRectFilledMultiColor(ImVec2(bb.Min.x, bb.Min.y), ImVec2(bb.Max.x, bb.Max.y), ImColor(39, 39, 40, int(alphamodulate * 253)), ImColor(39, 39, 40, int(alphamodulate * 253)), ImColor(51, 51, 51, int(alphamodulate * 253)), ImColor(51, 51, 51, int(alphamodulate * 253)));

	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(229 / 255.f, 229 / 255.f, 229 / 255.f, alphamodulate));
	ImGui::RenderText(ImVec2(bb.Min.x + style.ItemInnerSpacing.x + 0, bb.Min.y + style.FramePadding.y + 0), label);
	ImGui::PopStyleColor();

	return pressed;
}

bool beginchild(const char* str_id, const ImVec2& size_arg, bool border = false, ImGuiWindowFlags extra_flags = NULL)
{
	IM_USE;

	ImGuiWindow* window = GetCurrentWindow();
	return beginchildex(str_id, window->GetID(str_id), size_arg, border, extra_flags);
}

static float CalcMaxPopupHeightFromItemCount(int items_count)
{
	ImGuiContext& g = *GImGui;
	if (items_count <= 0)
		return FLT_MAX;
	return (g.FontSize + g.Style.ItemSpacing.y) * items_count - g.Style.ItemSpacing.y + (g.Style.WindowPadding.y * 2);
}

static bool Items_ArrayGetter(void* data, int idx, const char** out_text)
{
	const char* const* items = (const char* const*)data;
	if (out_text)
		*out_text = items[idx];
	return true;
}

// Getter for the old Combo() API: "item1\0item2\0item3\0"
static bool Items_SingleStringGetter(void* data, int idx, const char** out_text)
{
	// FIXME-OPT: we could pre-compute the indices to fasten this. But only 1 active combo means the waste is limited.
	const char* items_separated_by_zeros = (const char*)data;
	int items_count = 0;
	const char* p = items_separated_by_zeros;
	while (*p)
	{
		if (idx == items_count)
			break;
		p += strlen(p) + 1;
		items_count++;
	}
	if (!*p)
		return false;
	if (out_text)
		*out_text = p;
	return true;
}

__forceinline void padding(float x, float y)
{
	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + x * qgui::get().dpi_scale);
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + y * qgui::get().dpi_scale);
}

bool          combo(const char* label, int& current_item, const char* const items[], int items_count, int popup_max_height_in_items = -1);
bool          combo(const char* label, int& current_item, const char* items_separated_by_zeros, int popup_max_height_in_items = -1);      // Separate items with \0 within a string, end item-list with \0\0. e.g. "One\0Two\0Three\0"
bool          combo(const char* label, int& current_item, bool(*items_getter)(void* data, int idx, const char** out_text), void* data, int items_count, int popup_max_height_in_items = -1);

bool begincombo(const char* label, const char* preview_value, ImGuiComboFlags flags)
{
	IM_USE;
	ImGuiContext& g = *GImGui;
	bool has_window_size_constraint = (g.NextWindowData.Flags & ImGuiNextWindowDataFlags_HasSizeConstraint) != 0;
	g.NextWindowData.Flags &= ~ImGuiNextWindowDataFlags_HasSizeConstraint;

	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return false;

	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);

	const float arrow_size = (flags & ImGuiComboFlags_NoArrowButton) ? 0.0f : ImGui::GetFrameHeight();
	const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);
	const float expected_w = 240;
	const float w = (flags & ImGuiComboFlags_NoPreview) ? 240 : 240;

	const ImRect frame_bb(window->DC.CursorPos + ImVec2(11, 0), window->DC.CursorPos + ImVec2(w + 0, label_size.y + style.FramePadding.y * 2.0f + 0) + ImVec2(15, 18));
	const ImRect total_bb(frame_bb.Min, frame_bb.Max + ImVec2(label_size.x > 0.0f ? style.ItemInnerSpacing.x + label_size.x : 0.0f, 0.0f));

	ImGui::ItemSize(total_bb, style.FramePadding.y);
	if (!ImGui::ItemAdd(total_bb, id, &frame_bb))
		return false;

	bool hovered, held;
	bool pressed = ImGui::ButtonBehavior(frame_bb, id, &hovered, &held);
	bool popup_open = ImGui::IsPopupOpen(id, ImGuiPopupFlags_None);

	if (hovered || held)
		ImGui::SetMouseCursor(7);

	const float value_x2 = ImMax(frame_bb.Min.x, frame_bb.Max.x - arrow_size);

	if (!hovered)
		window->DrawList->AddRectFilledMultiColor(ImVec2(frame_bb.Min.x + 0, frame_bb.Min.y + 18), ImVec2(frame_bb.Max.x - 15, frame_bb.Max.y + 0), ImColor(51, 51, 51, int(alphamodulate * 253)), ImColor(51, 51, 51, int(alphamodulate * 253)), ImColor(39, 39, 40, int(alphamodulate * 253)), ImColor(39, 39, 40, int(alphamodulate * 253)));
	else
		window->DrawList->AddRectFilledMultiColor(ImVec2(frame_bb.Min.x + 0, frame_bb.Min.y + 18), ImVec2(frame_bb.Max.x - 15, frame_bb.Max.y + 0), ImColor(39, 39, 40, int(alphamodulate * 253)), ImColor(39, 39, 40, int(alphamodulate * 253)), ImColor(51, 51, 51, int(alphamodulate * 253)), ImColor(51, 51, 51, int(alphamodulate * 253)));

	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(229 / 255.f, 229 / 255.f, 229 / 255.f, alphamodulate));
	if (preview_value != NULL && !(flags & ImGuiComboFlags_NoPreview))
		ImGui::RenderText(frame_bb.Min + style.FramePadding + ImVec2(0, 18), preview_value);
	ImGui::PopStyleColor();

	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(229 / 255.f, 229 / 255.f, 229 / 255.f, alphamodulate));
	if (label_size.x > 0)
		ImGui::RenderText(ImVec2(frame_bb.Min.x, frame_bb.Min.y + style.FramePadding.y + 0), label);
	ImGui::PopStyleColor();

	if ((pressed || g.NavActivateId == id) && !popup_open)
	{
		if (window->DC.NavLayerCurrent == 0)
			window->NavLastIds[0] = id;
		ImGui::OpenPopupEx(id, ImGuiPopupFlags_None);
		popup_open = true;
	}

	if (!popup_open)
		return false;

	if ((flags & ImGuiComboFlags_HeightMask_) == 0)
		flags |= ImGuiComboFlags_HeightRegular;
	IM_ASSERT(ImIsPowerOfTwo(flags & ImGuiComboFlags_HeightMask_));
	int popup_max_height_in_items = -1;
	if (flags & ImGuiComboFlags_HeightRegular)
		popup_max_height_in_items = 8;
	else if (flags & ImGuiComboFlags_HeightSmall)
		popup_max_height_in_items = 4;
	else if (flags & ImGuiComboFlags_HeightLarge)
		popup_max_height_in_items = 20;
	ImGui::SetNextWindowSizeConstraints(ImVec2(w - 11, 0.0f), ImVec2(FLT_MAX, CalcMaxPopupHeightFromItemCount(popup_max_height_in_items)));

	char name[16];
	ImFormatString(name, IM_ARRAYSIZE(name), "##Combo_%02d", g.BeginPopupStack.Size);

	if (ImGuiWindow* popup_window = ImGui::FindWindowByName(name))
		if (popup_window->WasActive)
		{
			ImVec2 size_expected = ImGui::CalcWindowExpectedSize(popup_window);
			if (flags & ImGuiComboFlags_PopupAlignLeft)
				popup_window->AutoPosLastDirection = ImGuiDir_Left;
			ImRect r_outer = ImGui::GetWindowAllowedExtentRect(popup_window);
			ImVec2 pos = ImGui::FindBestWindowPosForPopupEx(frame_bb.GetBL(), size_expected, &popup_window->AutoPosLastDirection, r_outer, frame_bb, ImGuiPopupPositionPolicy_ComboBox);
			ImGui::SetNextWindowPos(pos);
		}

	ImGuiWindowFlags window_flags = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_Popup | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(style.FramePadding.x, style.WindowPadding.y));
	bool ret = ImGui::Begin(name, NULL, window_flags);
	ImGui::PopStyleVar();

	if (!ret)
	{
		ImGui::EndPopup();
		return false;
	}
	return true;
}

bool combo(const char* label, int& current_item, bool (*items_getter)(void*, int, const char**), void* data, int items_count, int popup_max_height_in_items)
{
	IM_USE;
	ImGuiContext& g = *GImGui;

	// Call the getter to obtain the preview string which is a parameter to BeginCombo()
	const char* preview_value = NULL;
	if (current_item >= 0 && current_item < items_count)
		items_getter(data, current_item, &preview_value);

	// The old Combo() API exposed "popup_max_height_in_items". The new more general BeginCombo() API doesn't have/need it, but we emulate it here.
	if (popup_max_height_in_items != -1 && !(g.NextWindowData.Flags & ImGuiNextWindowDataFlags_HasSizeConstraint))
		SetNextWindowSizeConstraints(ImVec2(0, 0), ImVec2(FLT_MAX, CalcMaxPopupHeightFromItemCount(popup_max_height_in_items)));

	if (!begincombo(label, preview_value, ImGuiComboFlags_None))
		return false;

	// FIXME-OPT: Use clipper (but we need to disable it on the appearing frame to make sure our call to SetItemDefaultFocus() is processed)
	bool value_changed = false;
	for (int i = 0; i < items_count; i++)
	{
		PushID((void*)(intptr_t)i);
		const bool item_selected = (i == current_item);
		const char* item_text;
		if (!items_getter(data, i, &item_text))
			item_text = "*Unknown item*";
		if (Selectable(item_text, item_selected))
		{
			value_changed = true;
			current_item = i;
		}
		if (item_selected)
			SetItemDefaultFocus();
		PopID();
	}

	EndCombo();
	return value_changed;
}

// Combo box helper allowing to pass an array of strings.
bool combo(const char* label, int& current_item, const char* const items[], int items_count, int height_in_items)
{
	IM_USE;
	const bool value_changed = combo(label, current_item, Items_ArrayGetter, (void*)items, items_count, height_in_items);
	return value_changed;
}

// Combo box helper allowing to pass all items in a single string literal holding multiple zero-terminated items "item1\0item2\0"
bool combo(const char* label, int& current_item, const char* items_separated_by_zeros, int height_in_items)
{
	IM_USE;
	int items_count = 0;
	const char* p = items_separated_by_zeros;       // FIXME-OPT: Avoid computing this, or at least only when combo is open
	while (*p)
	{
		p += strlen(p) + 1;
		items_count++;
	}
	bool value_changed = combo(label, current_item, Items_SingleStringGetter, (void*)items_separated_by_zeros, items_count, height_in_items);
	return value_changed;
}

void draw_multicombo(std::string name, std::vector<int>& variable, const char* labels[], int count, std::string& preview)
{
	auto hashname = ("") + name; // we dont want to render name of combo

	for (auto i = 0, j = 0; i < count; i++)
	{
		if (variable[i])
		{
			if (j)
				preview += (", ") + (std::string)labels[i];
			else
				preview = labels[i];

			j++;
		}
	}

	if (begincombo(hashname.c_str(), preview.c_str(), NULL)) // draw start
	{
		ImGui::Spacing();
		ImGui::BeginGroup();
		{

			for (auto i = 0; i < count; i++)
				ImGui::Selectable(labels[i], (bool*)&variable[i], ImGuiSelectableFlags_DontClosePopups);

		}
		ImGui::EndGroup();
		ImGui::Spacing();

		ImGui::EndCombo();
	}

	preview = crypt_str("None"); // reset preview to use later
}

bool LabelClick_1(const char* label, bool* v, const char* unique_id)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return false;

	// The concatoff/on thingies were for my weapon config system so if we're going to make that, we still need this aids.
	char Buf[64];
	_snprintf(Buf, 62, crypt_str("%s"), label);

	char getid[128];
	sprintf_s(getid, 128, crypt_str("%s%s"), label, unique_id);


	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(getid);
	const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

	const ImRect check_bb(window->DC.CursorPos, ImVec2(label_size.y + style.FramePadding.y * 2 + window->DC.CursorPos.x, window->DC.CursorPos.y + label_size.y + style.FramePadding.y * 2));
	ImGui::ItemSize(check_bb, style.FramePadding.y);

	ImRect total_bb = check_bb;

	if (label_size.x > 0)
	{
		ImGui::SameLine(0, style.ItemInnerSpacing.x);
		const ImRect text_bb(ImVec2(window->DC.CursorPos.x, window->DC.CursorPos.y + style.FramePadding.y), ImVec2(window->DC.CursorPos.x + label_size.x, window->DC.CursorPos.y + style.FramePadding.y + label_size.y));

		ImGui::ItemSize(ImVec2(text_bb.GetWidth(), check_bb.GetHeight()), style.FramePadding.y);
		total_bb = ImRect(ImMin(check_bb.Min, text_bb.Min), ImMax(check_bb.Max, text_bb.Max));
	}

	if (!ImGui::ItemAdd(total_bb, id))
		return false;

	bool hovered, held;
	bool pressed = ImGui::ButtonBehavior(total_bb, id, &hovered, &held);
	if (pressed)
		*v = !(*v);

	if (*v)
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(112 / 255.F, 15 / 255.F, 247 / 255.F, 1.f));
	if (label_size.x > 0.0f)
		ImGui::RenderText(ImVec2(check_bb.GetTL().x + 12, check_bb.GetTL().y), Buf);
	if (*v)
		ImGui::PopStyleColor();

	return pressed;

}
void draw_keybind_1(const char* label, key_bind* key_bind, const char* unique_id)
{
	// reset bind if we re pressing esc
	if (key_bind->key == KEY_ESCAPE)
		key_bind->key = KEY_NONE;

	auto clicked = false;
	auto text = (std::string)m_inputsys()->ButtonCodeToString(key_bind->key);

	if (key_bind->key <= KEY_NONE || key_bind->key >= KEY_MAX)
		text = crypt_str("-");

	// if we clicked on keybind
	if (hooks::input_shouldListen && hooks::input_receivedKeyval == &key_bind->key)
	{
		clicked = true;
		text = crypt_str("...");
	}

	auto textsize = ImGui::CalcTextSize(text.c_str()).x + 8 * 1;
	auto labelsize = ImGui::CalcTextSize(label);

	ImGui::Text(label);
	ImGui::SameLine();

	ImGui::SetCursorPosX(ImGui::GetWindowSize().x - (ImGui::GetWindowSize().x - ImGui::CalcItemWidth()) - max(50 * 1, textsize));
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 3 * 1);

	if (ImGui::KeybindButton(text.c_str(), unique_id, ImVec2(max(50 * 1, textsize), 23 * 1), clicked))
		clicked = true;


	if (clicked)
	{
		hooks::input_shouldListen = true;
		hooks::input_receivedKeyval = &key_bind->key;
	}

	static auto hold = false, toggle = false;

	switch (key_bind->mode)
	{
	case HOLD:
		hold = true;
		toggle = false;
		break;
	case TOGGLE:
		toggle = true;
		hold = false;
		break;
	}

	if (ImGui::BeginPopup(unique_id))
	{
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 6 * 1);
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + ((ImGui::GetCurrentWindow()->Size.x / 2) - (ImGui::CalcTextSize(crypt_str("Hold")).x / 2)));
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() - 11);

		if (LabelClick_1(crypt_str("Hold"), &hold, unique_id))
		{
			if (hold)
			{
				toggle = false;
				key_bind->mode = HOLD;
			}
			else if (toggle)
			{
				hold = false;
				key_bind->mode = TOGGLE;
			}
			else
			{
				toggle = false;
				key_bind->mode = HOLD;
			}

			ImGui::CloseCurrentPopup();
		}

		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + ((ImGui::GetCurrentWindow()->Size.x / 2) - (ImGui::CalcTextSize(crypt_str("Toggle")).x / 2)));
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() - 11);
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 9 * 1);

		if (LabelClick_1(crypt_str("Toggle"), &toggle, unique_id))
		{
			if (toggle)
			{
				hold = false;
				key_bind->mode = TOGGLE;
			}
			else if (hold)
			{
				toggle = false;
				key_bind->mode = HOLD;
			}
			else
			{
				hold = false;
				key_bind->mode = TOGGLE;
			}

			ImGui::CloseCurrentPopup();
		}

		ImGui::EndPopup();
	}
}

bool tab(const char* label, bool selected)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);
	const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

	ImVec2 pos = window->DC.CursorPos;
	ImVec2 size = ImGui::CalcItemSize({ 76,78 }, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);

	const ImRect bb(pos, pos + size);
	ImGui::ItemSize(size, style.FramePadding.y);
	if (!ImGui::ItemAdd(bb, id))
		return false;

	bool hovered, held;
	bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, NULL);

	if (hovered || held)
		ImGui::SetMouseCursor(7);

	float t = selected ? 1.0f : 0.0f;
	float ANIM_SPEED = 0.50f; // Bigger = Slower
	if (g.LastActiveId == g.CurrentWindow->GetID(label)) {
		float t_anim = ImSaturate(g.LastActiveIdTimer / ANIM_SPEED);
		t = selected ? (t_anim) : (1.0f - t_anim);
	}

	ImVec4 col = ImLerp(ImVec4{ 229 / 255.f, 229 / 255.f, 229 / 255.f, alphamodulate }, ImVec4{ 112 / 255.f, 15 / 255.f, 247 / 255.f, alphamodulate }, t);


	window->DrawList->AddLine(ImVec2(bb.Min.x + 20, bb.Min.y + 81), ImVec2(bb.Max.x - 20, bb.Min.y + 81), ImColor(59, 59, 59, int(alphamodulate * 255)));

	if (!selected)
		ImGui::PushStyleColor(ImGuiCol_Text, col);
	else
		ImGui::PushStyleColor(ImGuiCol_Text, col);

	ImGui::RenderText(ImVec2(bb.Min.x + 0 + (76 / 2 - label_size.x / 2), bb.Min.y + style.FramePadding.y + 35), label);
	ImGui::PopStyleColor();

	return pressed;
}

bool subtab(const char* label, bool selected, ImVec2 size_arg = ImVec2(0, 0))
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);
	const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

	ImVec2 pos = window->DC.CursorPos;
	ImVec2 size = ImGui::CalcItemSize(size_arg, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);

	const ImRect bb(pos, pos + size);
	ImGui::ItemSize(size, style.FramePadding.y);
	if (!ImGui::ItemAdd(bb, id))
		return false;

	float t = selected ? 1.0f : 0.0f;
	float ANIM_SPEED = 0.50f; // Bigger = Slower
	if (g.LastActiveId == g.CurrentWindow->GetID(label)) {
		float t_anim = ImSaturate(g.LastActiveIdTimer / ANIM_SPEED);
		t = selected ? (t_anim) : (1.0f - t_anim);
	}

	bool hovered, held;
	bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, NULL);

	if (hovered || held)
		ImGui::SetMouseCursor(7);

	ImVec4 col = ImLerp(ImVec4{ 140 / 255.f, 140 / 255.f, 140 / 255.f, alphamodulate }, ImVec4{ 112 / 255.f, 15 / 255.f, 247 / 255.f, alphamodulate }, t);
	ImVec4 col2 = ImLerp(ImVec4{ 140 / 255.f, 140 / 255.f, 140 / 255.f, 0 / 255.f }, ImVec4{ 112 / 255.f, 15 / 255.f, 247 / 255.f, alphamodulate }, t);

	ImGui::PushStyleColor(ImGuiCol_Text, col);
	ImGui::RenderText(ImVec2(bb.Min.x + (size_arg.x / 2 - label_size.x / 2), bb.Min.y + (size_arg.y / 2 - label_size.y / 2)), label);
	ImGui::PopStyleColor();

	window->DrawList->AddLine(bb.Min + ImVec2(40, size_arg.y), bb.Max - ImVec2(40, 0), ImGui::GetColorU32(col2));

	return pressed;
}

static const char* PatchFormatStringFloatToInt(const char* fmt)
{
	if (fmt[0] == '%' && fmt[1] == '.' && fmt[2] == '0' && fmt[3] == 'f' && fmt[4] == 0)
		return "%d";

	const char* fmt_start = ImParseFormatFindStart(fmt);
	const char* fmt_end = ImParseFormatFindEnd(fmt_start);
	if (fmt_end > fmt_start && fmt_end[-1] == 'f')
	{
		if (fmt_start == fmt && fmt_end[0] == 0)
			return "%d";
		ImGuiContext& g = *GImGui;
		ImFormatString(g.TempBuffer, IM_ARRAYSIZE(g.TempBuffer), "%.*s%%d%s", (int)(fmt_start - fmt), fmt, fmt_end);
		return g.TempBuffer;
	}
	return fmt;
}

bool SliderScalar(const char* label, ImGuiDataType data_type, void* p_data, const void* p_min, const void* p_max, const char* format, ImGuiSliderFlags flags)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);
	const float w = 240;

	const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);
	const ImRect frame_bb(window->DC.CursorPos + ImVec2(12, 18), window->DC.CursorPos + ImVec2(w + 0, label_size.y + 5 + (style.FramePadding.y * 2)));
	const ImRect total_bb(frame_bb.Min + ImVec2(12, -18), frame_bb.Max + ImVec2(0, 1) + ImVec2(0.0f, 0.0f));

	ImGui::ItemSize(total_bb, style.FramePadding.y);
	if (!ImGui::ItemAdd(total_bb, id, &frame_bb))
		return false;

	if (format == NULL)
		format = ImGui::DataTypeGetInfo(data_type)->PrintFmt;
	else if (data_type == ImGuiDataType_S32 && strcmp(format, "%d") != 0)
		format = PatchFormatStringFloatToInt(format);
	const bool hovered = ImGui::ItemHoverable(frame_bb, id);
	const bool temp_input_allowed = (flags & ImGuiSliderFlags_NoInput) == 0;
	bool temp_input_is_active = temp_input_allowed && ImGui::TempInputIsActive(id);
	if (!temp_input_is_active)
	{
		const bool focus_requested = temp_input_allowed && ImGui::FocusableItemRegister(window, id);
		const bool clicked = (hovered && g.IO.MouseClicked[0]);
		if (focus_requested || clicked || g.NavActivateId == id || g.NavInputId == id)
		{
			ImGui::SetActiveID(id, window);
			ImGui::SetFocusID(id, window);
			ImGui::FocusWindow(window);
			g.ActiveIdUsingNavDirMask |= (1 << ImGuiDir_Left) | (1 << ImGuiDir_Right);
		}
	}
	if (!hovered)
	{
		window->DrawList->AddRectFilledMultiColor(ImVec2(frame_bb.Min.x + 0, frame_bb.Min.y + 0), ImVec2(frame_bb.Max.x + 0, frame_bb.Max.y + 0), ImColor(51, 51, 51, int(253 * alphamodulate)), ImColor(51, 51, 51, int(253 * alphamodulate)), ImColor(39, 39, 40, int(253 * alphamodulate)), ImColor(39, 39, 40, int(253 * alphamodulate)));
	}
	else
	{
		window->DrawList->AddRectFilledMultiColor(ImVec2(frame_bb.Min.x + 0, frame_bb.Min.y + 0), ImVec2(frame_bb.Max.x + 0, frame_bb.Max.y + 0), ImColor(51, 51, 51, int(253 * alphamodulate)), ImColor(51, 51, 51, int(253 * alphamodulate)), ImColor(39, 39, 40, int(253 * alphamodulate)), ImColor(39, 39, 40, int(253 * alphamodulate)));
	}

	ImRect grab_bb;
	const bool value_changed = ImGui::SliderBehavior2(frame_bb, id, data_type, p_data, p_min, p_max, format, flags, &grab_bb);

	grab_bb.Min = frame_bb.Min;
	grab_bb.Min += ImVec2(0, 0);
	grab_bb.Max += ImVec2(0, 2);

	if (!hovered)
	{
		window->DrawList->AddRectFilledMultiColor(ImVec2(grab_bb.Min.x + 0, grab_bb.Min.y + 0), ImVec2(grab_bb.Max.x + 0, grab_bb.Max.y + 0), ImColor(112, 15, 247, int(230 * alphamodulate)), ImColor(112, 15, 247, int(230 * alphamodulate)), ImColor(27, 56, 245, int(230 * alphamodulate)), ImColor(27, 56, 245, int(230 * alphamodulate)));
	}
	else
	{
		window->DrawList->AddRectFilledMultiColor(ImVec2(grab_bb.Min.x + 0, grab_bb.Min.y + 0), ImVec2(grab_bb.Max.x + 0, grab_bb.Max.y + 0), ImColor(27, 56, 245, int(230 * alphamodulate)), ImColor(27, 56, 245, int(230 * alphamodulate)), ImColor(106, 0, 255, int(230 * alphamodulate)), ImColor(106, 0, 255, int(230 * alphamodulate)));
	}

	char value_buf[64];
	const char* value_buf_end = value_buf + ImGui::DataTypeFormatString(value_buf, IM_ARRAYSIZE(value_buf), data_type, p_data, format);

	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(229 / 255.f, 229 / 255.f, 229 / 255.f, alphamodulate));
	ImGui::RenderText(ImVec2(frame_bb.Max.x - ImGui::CalcTextSize(value_buf).x, frame_bb.Min.y + style.FramePadding.y + -19), value_buf);
	ImGui::PopStyleColor();

	if (hovered)
		ImGui::SetMouseCursor(7);

	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(198 / 255.f, 198 / 255.f, 198 / 255.f, alphamodulate));
	ImGui::RenderText(ImVec2(frame_bb.Min.x, frame_bb.Min.y + style.FramePadding.y + -19), label);
	ImGui::PopStyleColor();
	return value_changed;
}

bool slider_float(const char* label, float* v, float v_min, float v_max, const char* format, ImGuiSliderFlags flags)
{
	return SliderScalar(label, ImGuiDataType_Float, v, &v_min, &v_max, format, flags);
}

bool SliderInt(const char* label, int* v, int v_min, int v_max, bool minimum_damage, const char* format)
{
	return SliderScalar(label, ImGuiDataType_S32, v, &v_min, &v_max, format, minimum_damage);
}

bool slider_int(const char* label, int* v, int v_min, int v_max, const char* format, ImGuiSliderFlags flags)
{
	return SliderScalar(label, ImGuiDataType_S32, v, &v_min, &v_max, format, flags);
}

void qgui::shadow(ImDrawList* drawlist, ImVec2 pos, ImVec2 size, ImVec4 color)
{
	while (true)
	{
		if (color.w <= 0.019f)
			break;

		drawlist->AddRect(pos, pos + size, ImGui::GetColorU32(color), 8);
		color.w -= color.w / 8;
		pos -= ImVec2(1.f, 1.f);
		size += ImVec2(2.f, 2.f);
	}
}

void qgui::render_decorations()
{
	draw->AddRect(ImVec2(p.x + 0, p.y + 0), ImVec2(p.x + 845, p.y + 560), ImColor(59, 59, 59, int(255 * alphamodulate)), 0, 15, 1.000000);
	draw->AddLine(ImVec2(p.x + 0, p.y + 30), ImVec2(p.x + 875, p.y + 30), ImColor(59, 59, 59, int(255 * alphamodulate)), 1.000000);
	//draw->AddImage(background, p, p + ImVec2{ 845.000000f / 2, 560.000000f / 2 });
	draw->AddRectFilledMultiColor(ImVec2(p.x + 100, p.y + 30), ImVec2(p.x + 437, p.y + 31), ImColor(59, 59, 59, 0), ImColor(112, 15, 247, int(230 * alphamodulate)), ImColor(112, 15, 247, int(230 * alphamodulate)), ImColor(59, 59, 59, 0));
	draw->AddRectFilledMultiColor(ImVec2(p.x + 437, p.y + 30), ImVec2(p.x + 745, p.y + 31), ImColor(112, 15, 247, int(230 * alphamodulate)), ImColor(59, 59, 59, 0), ImColor(59, 59, 59, 0), ImColor(112, 15, 247, int(230 * alphamodulate)));
	draw->AddRectFilled(ImVec2(p.x + 7, p.y + 37), ImVec2(p.x + 85, p.y + 530), ImColor(12, 12, 12, int(240 * alphamodulate)), 0, 15);
	draw->AddRect(ImVec2(p.x + 7, p.y + 37), ImVec2(p.x + 85, p.y + 530), ImColor(59, 59, 59, int(240 * alphamodulate)), 0, 15, 1.000000);
	draw->AddRect(ImVec2(p.x + 8, p.y + 38), ImVec2(p.x + 84, p.y + 529), ImColor(2, 2, 2, int(240 * alphamodulate)), 0, 15, 1.000000);
	draw->AddRectFilled(ImVec2(p.x + 92, p.y + 37), ImVec2(p.x + 838, p.y + 530), ImColor(12, 12, 12, int(240 * alphamodulate)), 0, 15);
	draw->AddRect(ImVec2(p.x + 92, p.y + 37), ImVec2(p.x + 838, p.y + 530), ImColor(59, 59, 59, int(240 * alphamodulate)), 0, 15, 1.000000);
	draw->AddRect(ImVec2(p.x + 93, p.y + 38), ImVec2(p.x + 837, p.y + 529), ImColor(3, 1, 1, int(240 * alphamodulate)), 0, 15, 1.000000);

	draw->AddLine(ImVec2(p.x + 92, p.y + 37 + 26), ImVec2(p.x + 838, p.y + 37 + 26), ImColor(59, 59, 59, int(220 * alphamodulate)), 1.000000);
}

void qgui::render_tabs()
{
	ImGui::PushFont(qgui::get().bigxd);

	ImGui::SetCursorPos({ (float)8, (float)38 });
	ImGui::BeginGroup();
	if (tab("ragebot", 1 == selectedtab))
		selectedtab = 1;
	if (tab("visuals", 2 == selectedtab))
		selectedtab = 2;
	if (tab("misc", 3 == selectedtab))
		selectedtab = 3;
	if (tab("configs", 4 == selectedtab))
		selectedtab = 4;
	ImGui::EndGroup();
}

void qgui::render_content()
{
	ImGui::PushFont(qgui::get().bigxd);

	ImGui::SetCursorPos({ (float)92, (float)38 });
	ImGui::BeginChild("workzone", ImVec2(838 - 92, 530 - 37));

	if (selectedtab == 1)
	{
		ImGui::BeginGroup();
		if (subtab("general", 0 == selectedsubtab, ImVec2(180, 25)))
			selectedsubtab = 0;
		ImGui::SameLine();
		if (subtab("weapons", 1 == selectedsubtab, ImVec2(180, 25)))
			selectedsubtab = 1;
		ImGui::SameLine();
		if (subtab("anti aim", 2 == selectedsubtab, ImVec2(180, 25)))
			selectedsubtab = 2;
		ImGui::SameLine();
		if (subtab("fakelag", 3 == selectedsubtab, ImVec2(180, 25)))
			selectedsubtab = 3;
		ImGui::EndGroup();

		ImGui::SetCursorPos({ 15,35 });

		if (selectedsubtab == 0)
		{
			ImGui::BeginChild("", ImVec2(838 - 92 - 30, 530 - 72));
			{
				beginchild("##ragegeneral", { 720,445 });
				{
					ImGui::Text(" ");
					checkbox("enable", &g_cfg.ragebot.enable);
					checkbox("silent aim", &g_cfg.ragebot.silent_aim);
					checkbox("auto wall", &g_cfg.ragebot.autowall);
					checkbox("auto fire", &g_cfg.ragebot.autoshoot);
					checkbox("auto scope", &g_cfg.ragebot.autoscope);

					ImGui::Text(" ");
					ImGui::SameLine();
					draw_keybind_1(("auto peek"), &g_cfg.misc.automatic_peek, ("##AUTOPEEK__HOTKEY"));

					ImGui::Spacing();
					ImGui::Spacing();

					ImGui::Text(" ");
					ImGui::SameLine();
					ImGui::Text("exploits:", Color(240, 240, 240, 240));

					checkbox(("insta stop"), &g_cfg.misc.fast_stop);
					checkbox(("no duck cooldown"), &g_cfg.misc.noduck);

					ImGui::Text(" ");
					ImGui::SameLine();
					draw_keybind_1(("fake duck"), &g_cfg.misc.fakeduck_key, ("##FAKEDUCK__HOTKEY"));

					checkbox("double tap", &g_cfg.ragebot.double_tap);
					ImGui::SameLine();
					draw_keybind_1((""), &g_cfg.ragebot.double_tap_key, ("##HOTKEY_DT"));

					checkbox("hide shots", &g_cfg.antiaim.hide_shots);

					ImGui::SameLine();
					draw_keybind_1((""), &g_cfg.antiaim.hide_shots_key, ("##HOTKEY_HIDESHOTS"));
				}
				ImGui::EndChild();
			}
			ImGui::EndChild();
		}
		else if (selectedsubtab == 1)
		{
			ImGui::BeginChild("workzone1", ImVec2(838 - 92 - 30, 530 - 72));
			{
				const char* rage_weapons[8] = { ("heavy pistols"), ("pistols"), ("smgs"), ("rifles"), ("auto"), ("scout"), ("awp"), ("heavy") };

				beginchild("##RageWeapons", { 720,445 });
				{
					ImGui::Text(" ");
					combo(("current weapon"), hooks::rage_weapon, rage_weapons, ARRAYSIZE(rage_weapons));
					ImGui::Spacing();
					padding(0, 3);
					draw_multicombo(("hitboxes"), g_cfg.ragebot.weapon[hooks::rage_weapon].hitboxes, hitboxes, ARRAYSIZE(hitboxes), preview);

					combo(("target selection"), g_cfg.ragebot.weapon[hooks::rage_weapon].selection_type, selection, ARRAYSIZE(selection));

					checkbox(("target safe points"), &g_cfg.ragebot.weapon[hooks::rage_weapon].prefer_safe_points);
					ImGui::Text(" ");
					ImGui::SameLine();
					draw_keybind_1(("force safe points"), &g_cfg.ragebot.safe_point_key, ("##HOKEY_FORCE_SAFE_POINTS"));
					ImGui::Spacing();
					checkbox(("target body aim"), &g_cfg.ragebot.weapon[hooks::rage_weapon].prefer_body_aim);
					ImGui::Text(" ");
					ImGui::SameLine();
					draw_keybind_1(("force body aim"), &g_cfg.ragebot.body_aim_key, ("##HOKEY_FORCE_BODY_AIM"));

					checkbox(("multipoint scale"), &g_cfg.ragebot.weapon[hooks::rage_weapon].static_point_scale);
					if (g_cfg.ragebot.weapon[hooks::rage_weapon].static_point_scale)
					{
						slider_float(("head multipoint scale"), &g_cfg.ragebot.weapon[hooks::rage_weapon].head_scale, 0.0f, 1.0f, g_cfg.ragebot.weapon[hooks::rage_weapon].head_scale ? ("%.2f") : ("--"), NULL);
						slider_float(("body multipoint scale"), &g_cfg.ragebot.weapon[hooks::rage_weapon].body_scale, 0.0f, 1.0f, g_cfg.ragebot.weapon[hooks::rage_weapon].body_scale ? ("%.2f") : ("--"), NULL);
					}

					SliderInt(("hitchance"), &g_cfg.ragebot.weapon[hooks::rage_weapon].hitchance_amount, 1, 100, NULL, NULL);

					checkbox(("auto stop"), &g_cfg.ragebot.weapon[hooks::rage_weapon].autostop);

					if (g_cfg.ragebot.weapon[hooks::rage_weapon].autostop)
						draw_multicombo(("modes"), g_cfg.ragebot.weapon[hooks::rage_weapon].autostop_modifiers, autostop_modifiers, ARRAYSIZE(autostop_modifiers), preview);

					SliderInt(("min visible dmg"), &g_cfg.ragebot.weapon[hooks::rage_weapon].minimum_visible_damage, 1, 120, true, NULL);

					if (g_cfg.ragebot.autowall)
						SliderInt(("min awall dmg"), &g_cfg.ragebot.weapon[hooks::rage_weapon].minimum_damage, 1, 120, true, NULL);

					ImGui::Text(" ");
					ImGui::SameLine();
					draw_keybind_1(("dmg override"), &g_cfg.ragebot.weapon[hooks::rage_weapon].damage_override_key, ("##HOTKEY__DAMAGE_OVERRIDE"));

					if (g_cfg.ragebot.weapon[hooks::rage_weapon].damage_override_key.key > KEY_NONE && g_cfg.ragebot.weapon[hooks::rage_weapon].damage_override_key.key < KEY_MAX)
						SliderInt(("min override dmg"), &g_cfg.ragebot.weapon[hooks::rage_weapon].minimum_override_damage, 1, 120, true, NULL);

				}
				ImGui::EndChild();
			}
			ImGui::EndChild();
		}
		else if (selectedsubtab == 2)
		{
			ImGui::BeginChild("workzone1", ImVec2(838 - 92 - 30, 530 - 72));
			{
				beginchild("##RageAA", { 720,445 });
				{
					ImGui::Text(" ");
					static auto type = 0;
					checkbox(("enable"), &g_cfg.antiaim.enable);

					combo(("presets"), g_cfg.antiaim.aapresets, presets, ARRAYSIZE(presets));
					padding(0, 3);
					combo(("pitch"), g_cfg.antiaim.pitch, pitch, ARRAYSIZE(pitch));
					padding(0, 3);
					combo(("yaw"), g_cfg.antiaim.yaw, yaw, ARRAYSIZE(yaw));
					padding(0, 3);
					ImGui::Text(" ");
					ImGui::SameLine();
					draw_keybind_1(("manual back"), &g_cfg.antiaim.manual_back, ("##HOTKEY_INVERT_BACK"));

					ImGui::Text(" ");
					ImGui::SameLine();
					draw_keybind_1(("manual left"), &g_cfg.antiaim.manual_left, ("##HOTKEY_INVERT_LEFT"));

					ImGui::Text(" ");
					ImGui::SameLine();
					draw_keybind_1(("manual right"), &g_cfg.antiaim.manual_right, ("##HOTKEY_INVERT_RIGHT"));

					checkbox(("manual indicator"), &g_cfg.antiaim.flip_indicator);
					ImGui::SameLine();
					ImGui::ColorEdit(("##invc"), &g_cfg.antiaim.flip_indicator_color, ALPHA, NULL);

					combo(("desync"), g_cfg.antiaim.desync, desync, ARRAYSIZE(desync));

					if (g_cfg.antiaim.desync)
					{
						padding(0, 3);
						combo(("lby type"), g_cfg.antiaim.legit_lby_type, lby_type, ARRAYSIZE(lby_type));
					}

					padding(0, 3);
					combo(("base angle"), g_cfg.antiaim.base_angle, baseangle, ARRAYSIZE(baseangle));

					SliderInt(("desync amount"), &g_cfg.antiaim.desync_range, 1, 60, NULL, NULL);
					ImGui::Text(" ");
					ImGui::SameLine();
					draw_keybind_1(("invert"), &g_cfg.antiaim.flip_desync, ("##HOTKEY_INVERT_DESYNC"));

					if (g_cfg.antiaim.flip_desync.key > KEY_NONE && g_cfg.antiaim.flip_desync.key < KEY_MAX)
					{
						SliderInt(("inverted desync amount"), &g_cfg.antiaim.inverted_desync_range, 1, 60, NULL, NULL);
					}

					checkbox(("reversed freestanding"), &g_cfg.antiaim.break_resolver);
					checkbox(("Invert on doubletap"), &g_cfg.antiaim.invert_double_tap);
					ImGui::Text(" ");
					ImGui::SameLine();
					draw_keybind_1(("slowwalk"), &g_cfg.misc.slowwalk_key, ("##SLOWWALK__HOTKEY"));
					checkbox(("slidewalk"), &g_cfg.misc.slidewalk);

				}
				ImGui::EndChild();
			}
			ImGui::EndChild();
		}
		else if (selectedsubtab == 3)
		{
			ImGui::BeginChild("workzone1", ImVec2(838 - 92 - 30, 530 - 72));
			{
				beginchild("##RageFakelag", { 720,445 });
				{
					ImGui::Text(" ");
					checkbox(("fakelag"), &g_cfg.antiaim.fakelag);
					if (g_cfg.antiaim.fakelag)
					{
						combo(("fakelag mode"), g_cfg.antiaim.fakelag_type, fakelags, ARRAYSIZE(fakelags));
						SliderInt(("Limit"), &g_cfg.antiaim.fakelag_amount, 1, 16, NULL, NULL);

						draw_multicombo(("fakelag triggers"), g_cfg.antiaim.fakelag_enablers, lagstrigger, ARRAYSIZE(lagstrigger), preview);

						auto enabled_fakelag_triggers = false;

						for (auto i = 0; i < ARRAYSIZE(lagstrigger); i++)
							if (g_cfg.antiaim.fakelag_enablers[i])
								enabled_fakelag_triggers = true;

						if (enabled_fakelag_triggers)
							SliderInt(("triggers limit"), &g_cfg.antiaim.triggers_fakelag_amount, 1, 16, NULL, NULL);
					}
				}
				ImGui::EndChild();
			}
			ImGui::EndChild();
		}
	}
	else if (selectedtab == 2)
	{
		ImGui::BeginGroup();
		if (subtab("player esp", 0 == selectedsubtab, ImVec2(144, 25)))
			selectedsubtab = 0;
		ImGui::SameLine();
		if (subtab("glow", 1 == selectedsubtab, ImVec2(144, 25)))
			selectedsubtab = 1;
		ImGui::SameLine();
		if (subtab("other esp", 2 == selectedsubtab, ImVec2(144, 25)))
			selectedsubtab = 2;
		ImGui::SameLine();
		if (subtab("world esp", 3 == selectedsubtab, ImVec2(144, 25)))
			selectedsubtab = 3;
		ImGui::SameLine();
		if (subtab("chams", 4 == selectedsubtab, ImVec2(144, 25)))
			selectedsubtab = 4;
		ImGui::EndGroup();

		ImGui::SetCursorPos({ 15,35 });

		if (selectedsubtab == 0)
		{
			auto player = g_cfg.player.teams;

			ImGui::BeginChild("", ImVec2(838 - 92 - 30, 530 - 72));
			{
				beginchild("##PlayerESP", { 720,445 });
				{
					ImGui::Text(" ");
					checkbox(("enable"), &g_cfg.player.enable);
					combo(("team"), g_cfg.player.teams, player_teams, ARRAYSIZE(player_teams));

					if (player == 0 || ENEMY)
					{
						checkbox(("out of fov"), &g_cfg.player.arrows);
						ImGui::SameLine(-10, 0);
						ImGui::ColorEdit(("##arrowscolor"), &g_cfg.player.arrows_color, ALPHA, NULL);

						if (g_cfg.player.arrows)
						{
							SliderInt(("arrows distance"), &g_cfg.player.distance, 1, 100, NULL, NULL);
							SliderInt(("arrows size"), &g_cfg.player.size, 1, 100, NULL, NULL);
						}
					}

					checkbox(("name"), &g_cfg.player.type[player].name);
					ImGui::SameLine(-10, 0);
					ImGui::ColorEdit(("##namecolor"), &g_cfg.player.type[player].name_color, ALPHA, NULL);

					checkbox(("health"), &g_cfg.player.type[player].health);
					checkbox(("health color"), &g_cfg.player.type[player].custom_health_color);
					ImGui::SameLine(-10, 0);
					ImGui::ColorEdit(("##healthcolor"), &g_cfg.player.type[player].health_color, ALPHA, NULL);

					for (auto i = 0, j = 0; i < ARRAYSIZE(flags); i++)
					{
						if (g_cfg.player.type[player].flags[i])
						{
							if (j)
								preview += (", ") + (std::string)flags[i];
							else
								preview = flags[i];

							j++;
						}
					}

					draw_multicombo(("flags"), g_cfg.player.type[player].flags, flags, ARRAYSIZE(flags), preview);
					draw_multicombo(("weapon"), g_cfg.player.type[player].weapon, weaponplayer, ARRAYSIZE(weaponplayer), preview);


					if (g_cfg.player.type[player].weapon[WEAPON_ICON] || g_cfg.player.type[player].weapon[WEAPON_TEXT])
					{
						ImGui::Text(" ");
						ImGui::SameLine();
						ImGui::Text(("color "));
						ImGui::SameLine(-10, 0);
						ImGui::ColorEdit(("##weapcolor"), &g_cfg.player.type[player].weapon_color, ALPHA, NULL);
					}

					checkbox(("skeleton"), &g_cfg.player.type[player].skeleton);
					ImGui::SameLine(-10, 0);
					ImGui::ColorEdit(("##skeletoncolor"), &g_cfg.player.type[player].skeleton_color, ALPHA, NULL);

					checkbox(("ammo"), &g_cfg.player.type[player].ammo);
					ImGui::SameLine(-10, 0);
					ImGui::ColorEdit(("##ammocolor"), &g_cfg.player.type[player].ammobar_color, ALPHA, NULL);
				}
				ImGui::EndChild();
			}
			ImGui::EndChild();
		}
		else if (selectedsubtab == 1)
		{
			ImGui::BeginChild("workzone1", ImVec2(838 - 92 - 30, 530 - 72));
			{
				beginchild("glow", { 720,445 });
				{
					auto player = g_cfg.player.teams;
					ImGui::Text(" ");
					ImGui::Text(" ");
					ImGui::SameLine();
					combo(("set team"), g_cfg.player.teams, player_teams, ARRAYSIZE(player_teams));

					checkbox(("glow"), &g_cfg.player.type[player].glow);

					if (g_cfg.player.type[player].glow)
					{
						combo(("glow type"), g_cfg.player.type[player].glow_type, glowtype, ARRAYSIZE(glowtype));
						ImGui::SameLine(-10, 0);
						ImGui::ColorEdit(("##glowcolor"), &g_cfg.player.type[player].glow_color, ALPHA, NULL);
					}
				}
				ImGui::EndChild();
			}
			ImGui::EndChild();
		}
		else if (selectedsubtab == 2)
		{
			ImGui::BeginChild("workzone1", ImVec2(838 - 92 - 30, 530 - 72));
			{
				beginchild("##Other ESP", { 720,445 });
				{
					ImGui::Text(" ");
					ImGui::Text(" ");
					ImGui::SameLine();
					draw_keybind_1(("thirdperson"), &g_cfg.misc.thirdperson_toggle, ("##TPKEY__HOTKEY"));

					if (g_cfg.misc.thirdperson_toggle.key > KEY_NONE && g_cfg.misc.thirdperson_toggle.key < KEY_MAX)
						SliderInt(("third distance"), &g_cfg.misc.thirdperson_distance, 100, 300, NULL, NULL);

					checkbox(("thirdperson when dead"), &g_cfg.misc.thirdperson_when_spectating);

					checkbox(("aspect ratio"), &g_cfg.misc.aspect_ratio);
					if (g_cfg.misc.aspect_ratio)
					{
						padding(0, -10);
						slider_float(("amount"), &g_cfg.misc.aspect_ratio_amount, 0.5f, 2.0f, NULL, NULL);
					}

					SliderInt(("fov"), &g_cfg.esp.fov, 0, 89, NULL, NULL);


					ImGui::BeginChild(("##VISUAL2_FIRST"), ImVec2(317 * dpi_scale, (child_height - 35) * dpi_scale));
					{
						SliderInt(("viewmodel fov"), &g_cfg.esp.viewmodel_fov, 0, 89, NULL, NULL);
						SliderInt(("viewmodel X"), &g_cfg.esp.viewmodel_x, -50, 50, NULL, NULL);
						SliderInt(("viewmodel Y"), &g_cfg.esp.viewmodel_y, -50, 50, NULL, NULL);
						SliderInt(("viewmodel Z"), &g_cfg.esp.viewmodel_z, -50, 50, NULL, NULL);
						SliderInt(("viewmodel roll"), &g_cfg.esp.viewmodel_roll, -180, 180, NULL, NULL);
					}

					checkbox(("grenade pred"), &g_cfg.esp.grenade_prediction);
					ImGui::SameLine(-10, 0);
					ImGui::ColorEdit(("##grenpredcolor"), &g_cfg.esp.grenade_prediction_color, ALPHA, NULL);

					if (g_cfg.esp.grenade_prediction)
					{
						checkbox(("on click"), &g_cfg.esp.on_click);
						ImGui::SameLine(-10, 0);
						ImGui::ColorEdit(("##tracergrenpredcolor"), &g_cfg.esp.grenade_prediction_tracer_color, ALPHA, NULL);
					}

					//checkbox(("grenade esp"), &g_cfg.esp.projectiles);

					//checkbox(("grenade trails"), &g_cfg.esp.grenade_trail);

					checkbox(("bomb indicator"), &g_cfg.esp.bomb_timer);

					ImGui::Spacing();

					draw_multicombo(("removals"), g_cfg.esp.removals, removals, ARRAYSIZE(removals), preview);

					if (g_cfg.esp.removals[REMOVALS_ZOOM])
						checkbox(("fix sens"), &g_cfg.esp.fix_zoom_sensivity);



					checkbox(("client impacts"), &g_cfg.esp.client_bullet_impacts);

					ImGui::SameLine(-10, 0);
					ImGui::ColorEdit(("##clientbulletimpacts"), &g_cfg.esp.client_bullet_impacts_color, ALPHA, NULL);

					checkbox(("server impacts"), &g_cfg.esp.server_bullet_impacts);
					ImGui::SameLine(-10, 0);
					ImGui::ColorEdit(("##serverbulletimpacts"), &g_cfg.esp.server_bullet_impacts_color, ALPHA, NULL);

					checkbox(("local tracers"), &g_cfg.esp.bullet_tracer);
					ImGui::SameLine(-10, 0);
					ImGui::ColorEdit(("##bulltracecolor"), &g_cfg.esp.bullet_tracer_color, ALPHA, NULL);

					checkbox(("enemy tracers"), &g_cfg.esp.enemy_bullet_tracer);
					ImGui::SameLine(-10, 0);

					ImGui::ColorEdit(("##enemybulltracecolor"), &g_cfg.esp.enemy_bullet_tracer_color, ALPHA, NULL);

					combo(("hitmarker"), g_cfg.esp.hitmarkers, hitmarker, ARRAYSIZE(hitmarker));
					draw_multicombo(("hitmarker mode"), g_cfg.esp.hitmarker, hitmarkers, ARRAYSIZE(hitmarkers), preview);
					combo(("hitsound"), g_cfg.esp.hitsound, sounds, ARRAYSIZE(sounds));
					checkbox(("damage marker"), &g_cfg.esp.damage_marker);
					checkbox(("autowall crosshair"), &g_cfg.esp.penetration_reticle);
				}
				ImGui::EndChild();
			}
			ImGui::EndChild();
		}
		else if (selectedsubtab == 3)
		{
			ImGui::BeginChild("", ImVec2(838 - 92 - 30, 530 - 72));
			{
				beginchild("##WorldESP", { 720,445 });
				{
					ImGui::Text(" ");


					checkbox(("fullbright"), &g_cfg.esp.bright);

					combo(("skybox"), g_cfg.esp.skybox, skybox, ARRAYSIZE(skybox));

					ImGui::Text(" ");
					ImGui::SameLine();
					ImGui::Text(("color "));
					ImGui::SameLine(-10, 0);
					ImGui::ColorEdit(("##skyboxcolor"), &g_cfg.esp.skybox_color, ALPHA, NULL);

					if (g_cfg.esp.skybox == 21)
					{
						static char sky_custom[64] = "\0";

						if (!g_cfg.esp.custom_skybox.empty())
							strcpy_s(sky_custom, sizeof(sky_custom), g_cfg.esp.custom_skybox.c_str());

						ImGui::Text(" ");
						ImGui::SameLine();
						ImGui::Text(("name"));
						ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.f);

						if (ImGui::InputText(("##customsky"), sky_custom, sizeof(sky_custom)))
							g_cfg.esp.custom_skybox = sky_custom;

						ImGui::PopStyleVar();
					}

					checkbox(("world color"), &g_cfg.esp.nightmode);

					if (g_cfg.esp.nightmode)
					{
						ImGui::Text(" ");
						ImGui::SameLine();
						ImGui::Text(("world color "));
						ImGui::SameLine(-10, 0);
						ImGui::ColorEdit(("##worldcolor"), &g_cfg.esp.world_color, ALPHA, NULL);

						ImGui::Text(" ");
						ImGui::SameLine();
						ImGui::Text(("props color "));
						ImGui::SameLine(-10, 0);
						ImGui::ColorEdit(("##propscolor"), &g_cfg.esp.props_color, ALPHA, NULL);
					}
				}
				ImGui::EndChild();
			}
			ImGui::EndChild();
		}
		else if (selectedsubtab == 4)
		{
			ImGui::BeginChild("workzone1", ImVec2(838 - 92 - 30, 530 - 72));
			{
				beginchild("##Chams", { 720,445 });
				{
					auto player = g_cfg.player.teams;
					ImGui::Text(" ");
					combo(("set team"), g_cfg.player.teams, player_teams, ARRAYSIZE(player_teams));

					if (player != 2 || LOCAL || !g_cfg.player.local_chams_type)
						draw_multicombo(("chams"), g_cfg.player.type[player].chams, g_cfg.player.type[player].chams[PLAYER_CHAMS_VISIBLE] ? chamsvisact : chamsvis, g_cfg.player.type[player].chams[PLAYER_CHAMS_VISIBLE] ? ARRAYSIZE(chamsvisact) : ARRAYSIZE(chamsvis), preview);

					if (g_cfg.player.type[player].chams[PLAYER_CHAMS_VISIBLE] || player == 2 || LOCAL && g_cfg.player.local_chams_type) //-V648
					{
						if (player == LOCAL && g_cfg.player.local_chams_type)
						{
							draw_multicombo(("chams"), g_cfg.player.type[player].chams, g_cfg.player.type[player].chams[PLAYER_CHAMS_VISIBLE] ? chamsvisact : chamsvis, g_cfg.player.type[player].chams[PLAYER_CHAMS_VISIBLE] ? ARRAYSIZE(chamsvisact) : ARRAYSIZE(chamsvis), preview);
							combo(("type"), g_cfg.player.local_chams_type, local_chams_type, ARRAYSIZE(local_chams_type));




						}
						else
						{
							combo(("player chams"), g_cfg.player.type[player].chams_type, chamstype, ARRAYSIZE(chamstype));

							if (g_cfg.player.type[player].chams[PLAYER_CHAMS_VISIBLE])
							{
								ImGui::Text(" ");
								ImGui::SameLine();
								ImGui::Text(("visible "));
								ImGui::SameLine(-10, 0);
								ImGui::ColorEdit(("##chamsvisible"), &g_cfg.player.type[player].chams_color, ALPHA, NULL);
							}

							if (g_cfg.player.type[player].chams[PLAYER_CHAMS_INVISIBLE])
							{
								ImGui::Text(" ");
								ImGui::SameLine();
								ImGui::Text(("invisible "));
								ImGui::SameLine(-10, 0);
								ImGui::ColorEdit(("##chamsinvisible"), &g_cfg.player.type[player].xqz_color, ALPHA, NULL);
							}

							if (g_cfg.player.type[player].chams_type != 6)
							{
								checkbox(("player inner glow"), &g_cfg.player.type[player].double_material);
								ImGui::SameLine(-10, 0);
								ImGui::ColorEdit(("##doublematerialcolor"), &g_cfg.player.type[player].double_material_color, ALPHA, NULL);
							}

							if (player == 0 || ENEMY)
							{
								checkbox(("backtrack chams"), &g_cfg.player.backtrack_chams);

								if (g_cfg.player.backtrack_chams)
								{
									combo(("backtrack chams material"), g_cfg.player.backtrack_chams_material, chamstype, ARRAYSIZE(chamstype));

									ImGui::Text(" ");
									ImGui::SameLine();
									ImGui::Text(("color "));
									ImGui::SameLine(-10, 0);
									ImGui::ColorEdit(("##backtrackcolor"), &g_cfg.player.backtrack_chams_color, ALPHA, NULL);
								}
							}
							if (!g_cfg.player.local_chams_type)
							{
								checkbox(("player alpha in scope"), &g_cfg.player.transparency_in_scope);

								if (g_cfg.player.transparency_in_scope)
									slider_float(("alpha"), &g_cfg.player.transparency_in_scope_amount, 0.0f, 1.0f, NULL, NULL);
							}
							ImGui::Spacing();
							ImGui::Spacing();
							ImGui::Spacing();
							checkbox(("arm chams"), &g_cfg.esp.arms_chams);
							ImGui::SameLine(-10, 0);
							ImGui::ColorEdit(("##armscolor"), &g_cfg.esp.arms_chams_color, ALPHA, NULL);

							if (g_cfg.esp.arms_chams)
							{

								combo(("arm chams material"), g_cfg.esp.arms_chams_type, chamstype, ARRAYSIZE(chamstype));

								if (g_cfg.esp.arms_chams_type != 6)
								{
									checkbox(("arm inner glow"), &g_cfg.esp.arms_double_material);
									ImGui::SameLine(-10, 0);
									ImGui::ColorEdit(("##armsdoublematerial"), &g_cfg.esp.arms_double_material_color, ALPHA, NULL);
								}
							}

							checkbox(("weapon chams"), &g_cfg.esp.weapon_chams);
							ImGui::SameLine(-10, 0);
							ImGui::ColorEdit(("##weaponchamscolors"), &g_cfg.esp.weapon_chams_color, ALPHA, NULL);

							if (g_cfg.esp.weapon_chams)
							{
								combo(("weapon chams material"), g_cfg.esp.weapon_chams_type, chamstype, ARRAYSIZE(chamstype));

								if (g_cfg.esp.weapon_chams_type != 6)
								{
									checkbox(("weapon inner glow"), &g_cfg.esp.weapon_double_material);
									ImGui::SameLine(-10, 0);
									ImGui::ColorEdit(("##weapondoublematerial"), &g_cfg.esp.weapon_double_material_color, ALPHA, NULL);
								}
							}

							checkbox(("enable desync chams"), &g_cfg.player.fake_chams_enable);
							if (g_cfg.player.fake_chams_enable)
							{
								checkbox(("interpolate"), &g_cfg.player.visualize_lag);
								checkbox(("overlap"), &g_cfg.player.layered);
								combo(("player chams material"), g_cfg.player.fake_chams_type, chamstype, ARRAYSIZE(chamstype));

								ImGui::Text(" ");
								ImGui::SameLine();
								ImGui::Text(("color "));
								ImGui::SameLine(-10, 0);
								ImGui::ColorEdit(("##fakechamscolor"), &g_cfg.player.fake_chams_color, ALPHA, NULL);
							}

							checkbox(("onshot chams"), &g_cfg.onshot.chams_on_shot_enable);
							ImGui::SameLine(-10, 0);
							ImGui::ColorEdit(("onshot color"), &g_cfg.onshot.chams_on_shot_color, ALPHA, NULL);
							if (g_cfg.onshot.chams_on_shot_enable)
							{
								combo(("onshot material"), g_cfg.onshot.chams_on_shot_type, chamstype, ARRAYSIZE(chamstype));
							}
						}
					}
				}
				ImGui::EndChild();
			}
			ImGui::EndChild();
		}
		ImGui::EndChild();
	}
	else if (selectedtab == 3)
	{
		ImGui::BeginGroup();
		if (subtab("main misc", 0 == selectedsubtab, ImVec2(240, 25)))
			selectedsubtab = 0;
		ImGui::SameLine();
		if (subtab("other misc", 1 == selectedsubtab, ImVec2(240, 25)))
			selectedsubtab = 1;
		ImGui::SameLine();
		if (subtab("extra", 2 == selectedsubtab, ImVec2(240, 25)))
			selectedsubtab = 2;
		ImGui::EndGroup();

		ImGui::SetCursorPos({ 15,35 });

		if (selectedsubtab == 0)
		{
			ImGui::BeginChild("workzone1", ImVec2(838 - 92 - 30, 530 - 72));
			{
				beginchild("##Misc", { 720,445 });
				{
					ImGui::Text(" ");
					checkbox(("unlock inventory access"), &g_cfg.misc.inventory_access);
					checkbox(("preserve killfeed"), &g_cfg.esp.preserve_killfeed);

					checkbox(("watermark"), &g_cfg.menu.watermark);
					checkbox(("clantag"), &g_cfg.misc.clantag_spammer);
					checkbox(("spectators list"), &g_cfg.misc.spectators_list);

					if (g_cfg.misc.spectators_list)
					{
						static int width_s, height_s;

						m_engine()->GetScreenSize(width_s, height_s);

						SliderInt(("position x"), &g_cfg.misc.spec_x, 0, width_s, NULL, NULL);
						SliderInt(("position y"), &g_cfg.misc.spec_y, 0, height_s, NULL, NULL);
					}

					ImGui::Spacing();
					ImGui::Spacing();
					ImGui::Spacing();

					ImGui::Text(" ");
					ImGui::SameLine();
					ImGui::Text("movement:");
					checkbox(("bhop"), &g_cfg.misc.bunnyhop);
					combo(("autostrafe"), g_cfg.misc.airstrafe, strafes, ARRAYSIZE(strafes));

				}
				ImGui::EndChild();
			}
			ImGui::EndChild();
		}
		else if (selectedsubtab == 1)
		{
			ImGui::BeginChild("workzone1", ImVec2(838 - 92 - 30, 530 - 72));
			{

				beginchild("##Other", { 720,445 });
				{
					ImGui::Text(" ");
					draw_multicombo(("logs"), g_cfg.misc.events_to_log, events, ARRAYSIZE(events), preview);
					padding(0, 3);
					draw_multicombo(("logs output"), g_cfg.misc.log_output, events_output, ARRAYSIZE(events_output), preview);

					if (g_cfg.misc.events_to_log[EVENTLOG_HIT] || g_cfg.misc.events_to_log[EVENTLOG_ITEM_PURCHASES])
					{
						ImGui::Text(" ");
						ImGui::SameLine();
						ImGui::Text(("color "));
						ImGui::SameLine(-10, 0);
						ImGui::ColorEdit(("##logcolor"), &g_cfg.misc.log_color, ALPHA, NULL);
					}

					checkbox(("show csgo logs"), &g_cfg.misc.show_default_log);

					checkbox(("keybinds"), &g_cfg.misc.draw_keys);

					if (g_cfg.misc.draw_keys)
					{
						static int width_screen, height_screen;

						m_engine()->GetScreenSize(width_screen, height_screen);

						SliderInt(("position x"), &g_cfg.misc.key_x, 0, width_screen, NULL, NULL);
						SliderInt(("position y"), &g_cfg.misc.key_y, 0, height_screen, NULL, NULL);
					}

					checkbox(("Indicators"), &g_cfg.esp.indicators);
					checkbox(("Enable buybot"), &g_cfg.misc.buybot_enable);

					if (g_cfg.misc.buybot_enable)
					{
						combo(("main"), g_cfg.misc.buybot1, mainwep, ARRAYSIZE(mainwep));
						padding(0, 3);
						combo(("secondary"), g_cfg.misc.buybot2, secwep, ARRAYSIZE(secwep));
						padding(0, 3);
						draw_multicombo(("other"), g_cfg.misc.buybot3, grenades, ARRAYSIZE(grenades), preview);
					}
				}
				ImGui::EndChild();

			}
			ImGui::EndChild();
		}
		else if (selectedsubtab == 2)
		{
			ImGui::BeginChild("workzone1", ImVec2(838 - 92 - 30, 530 - 72));
			{
				beginchild("##extra", { 720,445 });
				{
					ImGui::Text(" ");
					ImGui::Text("coming soon: ");
					combo(("background effect"), g_cfg.misc.background, backgrounds, ARRAYSIZE(backgrounds));
					checkbox(("always on"), &g_cfg.misc.force_background);
					combo(("minigames"), g_cfg.misc.minigames, minigame, ARRAYSIZE(minigame));

				}
				ImGui::EndChild();
			}
			ImGui::EndChild();
		}
	}
	else if (selectedtab == 4)
	{
		ImGui::BeginGroup();
		if (subtab("configs", 0 == selectedsubtab, ImVec2(720, 25)))
			selectedsubtab = 0;
		ImGui::EndGroup();

		ImGui::SetCursorPos({ 15,35 });

		if (selectedsubtab == 0)
		{
			ImGui::BeginChild("workzone1", ImVec2(838 - 92 - 30, 530 - 72));
			{
				beginchild("##Configs", { 600,400 });
				{
					ImGui::PushItemWidth(300 * qgui::get().dpi_scale);

					static auto should_update = true;

					if (should_update)
					{
						should_update = false;

						cfg_manager->config_files();
						files = cfg_manager->files;
					}

					ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.f);
					ImGui::Text("");
					ImGui::Text(" ");
					ImGui::SameLine();
					ImGui::ListBoxConfigArray(("##CONFIGS"), &g_cfg.selected_config, files, 7);
					ImGui::PopStyleVar();

					static char config_name[64] = "\0";

					ImGui::Spacing();
					ImGui::Spacing();
					ImGui::Spacing();
					ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.f);
					ImGui::Text(" ");
					ImGui::SameLine();
					ImGui::InputText(("##configname"), config_name, sizeof(config_name));


					if (button(("refresh"), ImVec2(200 * dpi_scale, 20 * dpi_scale)))
					{
						cfg_manager->config_files();
						files = cfg_manager->files;
					}
					if (button(("create"), ImVec2(200 * dpi_scale, 20 * dpi_scale)))
					{
						g_cfg.new_config_name = config_name;
						add_config();
					}


					if (button(("save"), ImVec2(200 * dpi_scale, 20 * dpi_scale)))
						save_config();

					if (button(("load"), ImVec2(200 * dpi_scale, 20 * dpi_scale)))
						load_config();


					if (button(("delete"), ImVec2(200 * dpi_scale, 20 * dpi_scale)))
						remove_config();
				}
				ImGui::EndChild();
			}
			ImGui::EndChild();
		}
	}
	ImGui::EndChild();


}

void qgui::render_menu(bool is_open)
{
	ImGui::SetNextWindowPos({ 0,0 });
	ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
	ImGui::PushStyleColor(ImGuiCol_WindowBg, { 0,0,0,0 });
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	ImGui::Begin("##menu2", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoMove);
	ImGui::End();
	ImGui::PopStyleColor();
	ImGui::PopStyleVar();

	if (is_open && alphamodulate <= 1.f)
		alphamodulate += 0.05f;
	else if (!is_open && alphamodulate >= 0.f)
	{
		alphamodulate -= 0.05f;
	}

	auto flags = ImGuiWindowFlags_NoTitleBar | NULL | NULL | NULL | ImGuiWindowFlags_NoResize | NULL | NULL | NULL | NULL;

	ImGui::SetNextWindowSize({ 845.000000f,560.000000f });


	ImGui::PushStyleVar(ImGuiStyleVar_Alpha, alphamodulate);
	ImGui::Begin("Edited", nullptr, flags);
	{
		p = ImGui::GetWindowPos();
		draw = ImGui::GetWindowDrawList();

		render_decorations();
		render_tabs();
		render_content();

		draw->AddText(snazzyfont, { p.x + 845 / 2 - 10, p.y + 5 }, ImColor(112, 15, 247, int(255 * alphamodulate)), "Snazzy");
	}
	ImGui::End();
	ImGui::PopStyleVar(1);

	shadow(ImGui::GetOverlayDrawList(), p, { 845.000000f,560.000000f }, ImVec4(112 / 255.F, 15 / 255.F, 247 / 255.F, 0.25f * alphamodulate));
}