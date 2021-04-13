#include "misc.h"
#include "fakelag.h"
#include "..\ragebot\aim.h"
#include "..\visuals\world_esp.h"
#include "prediction_system.h"
#include "logs.h"
#include <random>

#define VERSION crypt_str("Snazzy v3 |")//

int pre_flags = 0;

void misc::edgebug(CUserCmd* pCmd) {

	if (g_ctx.local()->get_move_type() == MOVETYPE_LADDER || g_ctx.local()->get_move_type() == MOVETYPE_NOCLIP) return;

	if (engineprediction::get().backup_data.flags & FL_ONGROUND && !(g_ctx.local()->m_fFlags() & FL_ONGROUND))
		pCmd->m_buttons |= IN_DUCK;

}
bool jumpbugged = false;

void misc::jumpbug(CUserCmd* pCmd) {

	auto poop = g_ctx.local()->m_fFlags();
	bool unduck = false;
	static bool niggacheck = false;

	if ((g_ctx.local()->m_fFlags() & (1 << 0)) && !(engineprediction::get().backup_data.flags & (1 << 0))) {

		if (g_cfg.misc.bunnyhop) {
			g_cfg.misc.bunnyhop = false;
			niggacheck = true;
		}

		if (unduck) {
			pCmd->m_buttons &= ~IN_DUCK;
			pCmd->m_buttons |= IN_JUMP;
			unduck = false;
			jumpbugged = true;
		}

		pCmd->m_buttons |= IN_DUCK;
		pCmd->m_buttons &= ~IN_JUMP;
		unduck = true;
		jumpbugged = false;
	}
	else if (niggacheck) {
		g_cfg.misc.bunnyhop = true;
		niggacheck = false;
	}

}//
void misc::watermark()
{
	if (!g_cfg.menu.watermark)
		return;


	auto width = 0, height = 0;

	m_engine()->GetScreenSize(width, height); //-V807

	auto watermark = VERSION + g_ctx.username + crypt_str(" | ") + g_ctx.globals.time;

	if (m_engine()->IsInGame())
	{
		auto nci = m_engine()->GetNetChannelInfo();

		if (nci)
		{
			auto server = nci->GetAddress();

			if (!strcmp(server, crypt_str("loopback")))
				server = crypt_str("Local server");
			else if (m_gamerules()->m_bIsValveDS())
				server = crypt_str("Valve server");

			auto tickrate = std::to_string((int)(1.0f / m_globals()->m_intervalpertick));
			watermark = VERSION + g_ctx.username + crypt_str("") + server + crypt_str(" |") + crypt_str(" ping: ") + std::to_string(g_ctx.globals.ping) + crypt_str(" ms ");

		}
	}

	auto box_width = render::get().text_width(fonts[WATERMARK], watermark.c_str()) + 10;

	//background
	render::get().rect_filled(width - 10 - box_width, 11, box_width, 20, Color(25, 25, 25, 255));

	//line on top
	render::get().gradient(width - 10 - box_width, 11, box_width, 2.5, Color(113, 13, 219, 255), Color(113, 13, 219, 0), GRADIENT_HORIZONTAL);

	//line on bottom
	render::get().gradient(width - 10 - box_width, 31, box_width, 2.5, Color(113, 13, 219, 0), Color(113, 13, 219, 255), GRADIENT_HORIZONTAL);

	//line on left
	render::get().gradient(width - 10 - box_width, 11, box_width - box_width + 2.5, 22, Color(113, 13, 219, 255), Color(113, 13, 219, 0), GRADIENT_VERTICAL);

	//line on right
	render::get().gradient(width - box_width + box_width - 10, 11, box_width - box_width + 2.5, 22, Color(113, 13, 219, 0), Color(113, 13, 219, 255), GRADIENT_VERTICAL);

	//text
	render::get().text(fonts[WATERMARK], width - 10 - box_width + 5, 21, Color(255, 255, 255, 220), HFONT_CENTERED_Y, watermark.c_str());

}

void misc::NoDuck(CUserCmd* cmd)
{
	if (!g_cfg.misc.noduck)
		return;

	if (m_gamerules()->m_bIsValveDS())
		return;

	cmd->m_buttons |= IN_BULLRUSH;
}

void misc::ChangeRegion()
{
	switch (g_cfg.misc.region_changer) {
	case 0:
		m_engine()->ExecuteClientCmd("sdr SDRClient_ForceRelayCluster waw");
		break;
	case 1:
		m_engine()->ExecuteClientCmd("sdr SDRClient_ForceRelayCluster atl");
		break;
	case 2:
		m_engine()->ExecuteClientCmd("sdr SDRClient_ForceRelayCluster bom");
		break;
	case 3:
		m_engine()->ExecuteClientCmd("sdr SDRClient_ForceRelayCluster can");
		break;
	case 4:
		m_engine()->ExecuteClientCmd("sdr SDRClient_ForceRelayCluster canm");
		break;
	case 5:
		m_engine()->ExecuteClientCmd("sdr SDRClient_ForceRelayCluster cant");
		break;
	case 6:
		m_engine()->ExecuteClientCmd("sdr SDRClient_ForceRelayCluster canu");
		break;
	case 7:
		m_engine()->ExecuteClientCmd("sdr SDRClient_ForceRelayCluster dxb");
		break;
	case 8:
		m_engine()->ExecuteClientCmd("sdr SDRClient_ForceRelayCluster eat");
		break;
	case 9:
		m_engine()->ExecuteClientCmd("sdr SDRClient_ForceRelayCluster fra");
		break;
	case 10:
		m_engine()->ExecuteClientCmd("sdr SDRClient_ForceRelayCluster gru");
		break;//
	case 11:
		m_engine()->ExecuteClientCmd("sdr SDRClient_ForceRelayCluster hkg");
		break;
	case 12:
		m_engine()->ExecuteClientCmd("sdr SDRClient_ForceRelayCluster iad");
		break;
	case 13:
		m_engine()->ExecuteClientCmd("sdr SDRClient_ForceRelayCluster jnb");
		break;
	case 14:
		m_engine()->ExecuteClientCmd("sdr SDRClient_ForceRelayCluster lax");
		break;
	case 15:
		m_engine()->ExecuteClientCmd("sdr SDRClient_ForceRelayCluster lhr");
		break;
	case 16:
		m_engine()->ExecuteClientCmd("sdr SDRClient_ForceRelayCluster lim");
		break;
	case 17:
		m_engine()->ExecuteClientCmd("sdr SDRClient_ForceRelayCluster lux");
		break;
	case 18:
		m_engine()->ExecuteClientCmd("sdr SDRClient_ForceRelayCluster maa");
		break;
	case 19:
		m_engine()->ExecuteClientCmd("sdr SDRClient_ForceRelayCluster mad");
		break;
	case 20:
		m_engine()->ExecuteClientCmd("sdr SDRClient_ForceRelayCluster man");
		break;
	case 21:
		m_engine()->ExecuteClientCmd("sdr SDRClient_ForceRelayCluster okc");
		break;
	case 22:
		m_engine()->ExecuteClientCmd("sdr SDRClient_ForceRelayCluster ord");
		break;
	case 23:
		m_engine()->ExecuteClientCmd("sdr SDRClient_ForceRelayCluster par");
		break;
	case 24:
		m_engine()->ExecuteClientCmd("sdr SDRClient_ForceRelayCluster pwg");
		break;
	case 25:
		m_engine()->ExecuteClientCmd("sdr SDRClient_ForceRelayCluster pwj");
		break;
	case 26:
		m_engine()->ExecuteClientCmd("sdr SDRClient_ForceRelayCluster pwu");
		break;
	case 27:
		m_engine()->ExecuteClientCmd("sdr SDRClient_ForceRelayCluster pww");
		break;
	case 28:
		m_engine()->ExecuteClientCmd("sdr SDRClient_ForceRelayCluster pwz");
		break;
	case 29:
		m_engine()->ExecuteClientCmd("sdr SDRClient_ForceRelayCluster scl");
		break;
	case 30:
		m_engine()->ExecuteClientCmd("sdr SDRClient_ForceRelayCluster sea");
		break;
	case 31:
		m_engine()->ExecuteClientCmd("sdr SDRClient_ForceRelayCluster sgp");
		break;
	case 32:
		m_engine()->ExecuteClientCmd("sdr SDRClient_ForceRelayCluster sha");
		break;
	case 33:
		m_engine()->ExecuteClientCmd("sdr SDRClient_ForceRelayCluster sham");
		break;
	case 34:
		m_engine()->ExecuteClientCmd("sdr SDRClient_ForceRelayCluster shat");
		break;
	case 35:
		m_engine()->ExecuteClientCmd("sdr SDRClient_ForceRelayCluster shau");
		break;
	case 36:
		m_engine()->ExecuteClientCmd("sdr SDRClient_ForceRelayCluster shb");
		break;
	case 37:
		m_engine()->ExecuteClientCmd("sdr SDRClient_ForceRelayCluster sto");
		break;
	case 38:
		m_engine()->ExecuteClientCmd("sdr SDRClient_ForceRelayCluster sto2");
		break;
	case 39:
		m_engine()->ExecuteClientCmd("sdr SDRClient_ForceRelayCluster syd");
		break;
	case 40:
		m_engine()->ExecuteClientCmd("sdr SDRClient_ForceRelayCluster tsn");
		break;
	case 41:
		m_engine()->ExecuteClientCmd("sdr SDRClient_ForceRelayCluster tsnm");
		break;
	case 42:
		m_engine()->ExecuteClientCmd("sdr SDRClient_ForceRelayCluster tsnt");
		break;
	case 43:
		m_engine()->ExecuteClientCmd("sdr SDRClient_ForceRelayCluster tsnu");
		break;
	case 44:
		m_engine()->ExecuteClientCmd("sdr SDRClient_ForceRelayCluster tyo");
		break;
	case 45:
		m_engine()->ExecuteClientCmd("sdr SDRClient_ForceRelayCluster tyo1");
		break;
	case 46:
		m_engine()->ExecuteClientCmd("sdr SDRClient_ForceRelayCluster vie");
		break;
	case 47:
		m_engine()->ExecuteClientCmd("sdr SDRClient_ForceRelayCluster ams");
		break;
	}
}

void misc::ChatSpamer()
{
	if (!g_cfg.misc.chat)
		return;

	static std::string chatspam[] =
	{
		crypt_str("https://discord.gg/Eh9P4T7u9r"),
		crypt_str("Snazzy v3"),
	};

	static auto lastspammed = 0;

	if (GetTickCount() - lastspammed > 800)
	{
		lastspammed = GetTickCount();

		srand(m_globals()->m_tickcount);
		std::string msg = crypt_str("say ") + chatspam[rand() % 4];

		m_engine()->ExecuteClientCmd(msg.c_str());
	}
}

void misc::NameSpam() {
	if (!g_cfg.misc.name_spam)
		return;

	static bool steal = false;

	char* First_static = u8"\u265B Snazzy v3 \u265B";
	char* Second_static = u8"\u265B Snazzy v3 \u265B";

	ConVar* Name = m_cvar()->FindVar("name");
	*(int*)((DWORD)&Name->m_fnChangeCallbacks + 0xC) = 0;

	if (Name)
	{
		if (!steal)
		{
			Name->SetValue(First_static);
			steal = true;
		}
		else
		{
			Name->SetValue(Second_static);
			steal = false;
		}
	}
}

void misc::AutoCrouch(CUserCmd* cmd)
{
	if (fakelag::get().condition)
	{
		g_ctx.globals.fakeducking = false;
		return;
	}

	if (!(g_ctx.local()->m_fFlags() & FL_ONGROUND && engineprediction::get().backup_data.flags & FL_ONGROUND))
	{
		g_ctx.globals.fakeducking = false;
		return;
	}

	if (m_gamerules()->m_bIsValveDS())
	{
		g_ctx.globals.fakeducking = false;
		return;
	}

	if (!key_binds::get().get_key_bind_state(20))
	{
		g_ctx.globals.fakeducking = false;
		return;
	}

	if (!g_cfg.ragebot.fakeduck_fix) {
		if (!g_ctx.globals.fakeducking && m_clientstate()->iChokedCommands != 7)
			return;
	}
	else {
		if (!g_ctx.globals.fakeducking && m_clientstate()->iChokedCommands != 5)
			return;
	}

	if (!g_cfg.ragebot.fakeduck_fix) {
		if (m_clientstate()->iChokedCommands >= 7)
			cmd->m_buttons |= IN_DUCK;
		else
			cmd->m_buttons &= ~IN_DUCK;
	}
	else {
		if (m_clientstate()->iChokedCommands >= 3)
			cmd->m_buttons |= IN_DUCK;
		else
			cmd->m_buttons &= ~IN_DUCK;
	}

	g_ctx.globals.fakeducking = true;
}

void misc::SlideWalk(CUserCmd* cmd)
{
	if (!g_ctx.local()->is_alive()) //-V807
		return;

	if (g_ctx.local()->get_move_type() == MOVETYPE_LADDER)
		return;

	if (!(g_ctx.local()->m_fFlags() & FL_ONGROUND && engineprediction::get().backup_data.flags & FL_ONGROUND))
		return;

	if (antiaim::get().condition(cmd, true) && g_cfg.misc.slidewalk)
	{
		if (cmd->m_forwardmove > 0.0f)
		{
			cmd->m_buttons |= IN_BACK;
			cmd->m_buttons &= ~IN_FORWARD;
		}
		else if (cmd->m_forwardmove < 0.0f)
		{
			cmd->m_buttons |= IN_FORWARD;
			cmd->m_buttons &= ~IN_BACK;
		}

		if (cmd->m_sidemove > 0.0f)
		{
			cmd->m_buttons |= IN_MOVELEFT;
			cmd->m_buttons &= ~IN_MOVERIGHT;
		}
		else if (cmd->m_sidemove < 0.0f)
		{
			cmd->m_buttons |= IN_MOVERIGHT;
			cmd->m_buttons &= ~IN_MOVELEFT;
		}
	}
	else
	{
		auto buttons = cmd->m_buttons & ~(IN_MOVERIGHT | IN_MOVELEFT | IN_BACK | IN_FORWARD);

		if (g_cfg.misc.slidewalk)
		{
			if (cmd->m_forwardmove <= 0.0f)
				buttons |= IN_BACK;
			else
				buttons |= IN_FORWARD;

			if (cmd->m_sidemove > 0.0f)
				goto LABEL_15;
			else if (cmd->m_sidemove >= 0.0f)
				goto LABEL_18;

			goto LABEL_17;
		}
		else
			goto LABEL_18;

		if (cmd->m_forwardmove <= 0.0f) //-V779
			buttons |= IN_FORWARD;
		else
			buttons |= IN_BACK;

		if (cmd->m_sidemove > 0.0f)
		{
		LABEL_17:
			buttons |= IN_MOVELEFT;
			goto LABEL_18;
		}

		if (cmd->m_sidemove < 0.0f)
			LABEL_15:

		buttons |= IN_MOVERIGHT;

	LABEL_18:
		cmd->m_buttons = buttons;
	}
}

void misc::automatic_peek(CUserCmd* cmd, float wish_yaw)
{
	if (key_binds::get().get_key_bind_state(18))
	{
		if (g_ctx.globals.start_position.IsZero())
		{
			g_ctx.globals.start_position = g_ctx.local()->GetAbsOrigin();

			if (!(engineprediction::get().backup_data.flags & FL_ONGROUND))
			{
				Ray_t ray;
				CTraceFilterWorldAndPropsOnly filter;
				CGameTrace trace;

				ray.Init(g_ctx.globals.start_position, g_ctx.globals.start_position - Vector(0.0f, 0.0f, 1000.0f));
				m_trace()->TraceRay(ray, MASK_SOLID, &filter, &trace);

				if (trace.fraction < 1.0f)
					g_ctx.globals.start_position = trace.endpos + Vector(0.0f, 0.0f, 2.0f);
			}
		}
		else
		{
			auto revolver_shoot = g_ctx.globals.weapon->m_iItemDefinitionIndex() == WEAPON_REVOLVER && !g_ctx.globals.revolver_working && (cmd->m_buttons & IN_ATTACK || cmd->m_buttons & IN_ATTACK2);

			if (cmd->m_buttons & IN_ATTACK && g_ctx.globals.weapon->m_iItemDefinitionIndex() != WEAPON_REVOLVER || revolver_shoot)
				g_ctx.globals.fired_shot = true;

			if (g_ctx.globals.fired_shot)
			{
				auto current_position = g_ctx.local()->GetAbsOrigin();
				auto difference = current_position - g_ctx.globals.start_position;

				if (difference.Length2D() > 5.0f)
				{
					auto velocity = Vector(difference.x * cos(wish_yaw / 180.0f * M_PI) + difference.y * sin(wish_yaw / 180.0f * M_PI), difference.y * cos(wish_yaw / 180.0f * M_PI) - difference.x * sin(wish_yaw / 180.0f * M_PI), difference.z);

					cmd->m_forwardmove = -velocity.x * 20.0f;
					cmd->m_sidemove = velocity.y * 20.0f;
				}
				else
				{
					g_ctx.globals.fired_shot = false;
					g_ctx.globals.start_position.Zero();
				}
			}
		}
	}
	else
	{
		g_ctx.globals.fired_shot = false;
		g_ctx.globals.start_position.Zero();
	}
}

void misc::ViewModel()
{
	if (g_cfg.esp.viewmodel_fov)
	{
		auto viewFOV = (float)g_cfg.esp.viewmodel_fov + 68.0f;
		static auto viewFOVcvar = m_cvar()->FindVar(crypt_str("viewmodel_fov"));

		if (viewFOVcvar->GetFloat() != viewFOV) //-V550
		{
			*(float*)((DWORD)&viewFOVcvar->m_fnChangeCallbacks + 0xC) = 0.0f;
			viewFOVcvar->SetValue(viewFOV);
		}
	}

	if (g_cfg.esp.viewmodel_x)
	{
		auto viewX = (float)g_cfg.esp.viewmodel_x / 2.0f;
		static auto viewXcvar = m_cvar()->FindVar(crypt_str("viewmodel_offset_x")); //-V807

		if (viewXcvar->GetFloat() != viewX) //-V550
		{
			*(float*)((DWORD)&viewXcvar->m_fnChangeCallbacks + 0xC) = 0.0f;
			viewXcvar->SetValue(viewX);
		}
	}

	if (g_cfg.esp.viewmodel_y)
	{
		auto viewY = (float)g_cfg.esp.viewmodel_y / 2.0f;
		static auto viewYcvar = m_cvar()->FindVar(crypt_str("viewmodel_offset_y"));

		if (viewYcvar->GetFloat() != viewY) //-V550
		{
			*(float*)((DWORD)&viewYcvar->m_fnChangeCallbacks + 0xC) = 0.0f;
			viewYcvar->SetValue(viewY);
		}
	}

	if (g_cfg.esp.viewmodel_z)
	{
		auto viewZ = (float)g_cfg.esp.viewmodel_z / 2.0f;
		static auto viewZcvar = m_cvar()->FindVar(crypt_str("viewmodel_offset_z"));

		if (viewZcvar->GetFloat() != viewZ) //-V550
		{
			*(float*)((DWORD)&viewZcvar->m_fnChangeCallbacks + 0xC) = 0.0f;
			viewZcvar->SetValue(viewZ);
		}
	}
}

void misc::FullBright()
{
	if (!g_cfg.player.enable)
		return;

	static auto mat_fullbright = m_cvar()->FindVar(crypt_str("mat_fullbright"));

	if (mat_fullbright->GetBool() != g_cfg.esp.bright)
		mat_fullbright->SetValue(g_cfg.esp.bright);
}

void misc::PovArrows(player_t* e, Color color)
{
	auto isOnScreen = [](Vector origin, Vector& screen) -> bool
	{
		if (!math::world_to_screen(origin, screen))
			return false;

		static int iScreenWidth, iScreenHeight;
		m_engine()->GetScreenSize(iScreenWidth, iScreenHeight);

		auto xOk = iScreenWidth > screen.x;
		auto yOk = iScreenHeight > screen.y;

		return xOk && yOk;
	};

	Vector screenPos;

	if (isOnScreen(e->GetAbsOrigin(), screenPos))
		return;

	Vector viewAngles;
	m_engine()->GetViewAngles(viewAngles);

	static int width, height;
	m_engine()->GetScreenSize(width, height);

	auto screenCenter = Vector2D(width * 0.5f, height * 0.5f);
	auto angleYawRad = DEG2RAD(viewAngles.y - math::calculate_angle(g_ctx.globals.eye_pos, e->GetAbsOrigin()).y - 90.0f);

	auto radius = g_cfg.player.distance;
	auto size = g_cfg.player.size;

	auto newPointX = screenCenter.x + ((((width - (size * 3)) * 0.5f) * (radius / 100.0f)) * cos(angleYawRad)) + (int)(6.0f * (((float)size - 4.0f) / 16.0f));
	auto newPointY = screenCenter.y + ((((height - (size * 3)) * 0.5f) * (radius / 100.0f)) * sin(angleYawRad));

	std::array <Vector2D, 3> points
	{
		Vector2D(newPointX - size, newPointY - size),
		Vector2D(newPointX + size, newPointY),
		Vector2D(newPointX - size, newPointY + size)
	};

	math::rotate_triangle(points, viewAngles.y - math::calculate_angle(g_ctx.globals.eye_pos, e->GetAbsOrigin()).y - 90.0f);
	render::get().triangle(points.at(0), points.at(1), points.at(2), color);
}

void misc::zeus_range()
{
	if (!g_cfg.player.enable)
		return;

	if (!g_cfg.esp.taser_range)
		return;

	if (!m_input()->m_fCameraInThirdPerson)
		return;

	if (!g_ctx.local()->is_alive())  //-V807
		return;

	auto weapon = g_ctx.local()->m_hActiveWeapon().Get();

	if (!weapon)
		return;

	if (weapon->m_iItemDefinitionIndex() != WEAPON_TASER)
		return;

	auto weapon_info = weapon->get_csweapon_info();

	if (!weapon_info)
		return;

	render::get().Draw3DRainbowCircle(g_ctx.local()->get_shoot_position(), weapon_info->flRange);
}

void misc::NightmodeFix()
{
	static auto in_game = false;

	if (m_engine()->IsInGame() && !in_game)
	{
		in_game = true;

		g_ctx.globals.change_materials = true;
		worldesp::get().changed = true;

		static auto skybox = m_cvar()->FindVar(crypt_str("sv_skyname"));
		worldesp::get().backup_skybox = skybox->GetString();
		return;
	}
	else if (!m_engine()->IsInGame() && in_game)
		in_game = false;

	static auto player_enable = g_cfg.player.enable;

	if (player_enable != g_cfg.player.enable)
	{
		player_enable = g_cfg.player.enable;
		g_ctx.globals.change_materials = true;
		return;
	}

	static auto setting = g_cfg.esp.nightmode;

	if (setting != g_cfg.esp.nightmode)
	{
		setting = g_cfg.esp.nightmode;
		g_ctx.globals.change_materials = true;
		return;
	}

	static auto setting_world = g_cfg.esp.world_color;

	if (setting_world != g_cfg.esp.world_color)
	{
		setting_world = g_cfg.esp.world_color;
		g_ctx.globals.change_materials = true;
		return;
	}

	static auto setting_props = g_cfg.esp.props_color;

	if (setting_props != g_cfg.esp.props_color)
	{
		setting_props = g_cfg.esp.props_color;
		g_ctx.globals.change_materials = true;
	}
}

void misc::desync_arrows()
{
	if (!g_ctx.local()->is_alive())
		return;

	if (!g_cfg.ragebot.enable)
		return;

	if (!g_cfg.antiaim.enable)
		return;

	if ((g_cfg.antiaim.manual_back.key <= KEY_NONE || g_cfg.antiaim.manual_back.key >= KEY_MAX) && (g_cfg.antiaim.manual_left.key <= KEY_NONE || g_cfg.antiaim.manual_left.key >= KEY_MAX) && (g_cfg.antiaim.manual_right.key <= KEY_NONE || g_cfg.antiaim.manual_right.key >= KEY_MAX))
		antiaim::get().manual_side = SIDE_NONE;

	if (!g_cfg.antiaim.flip_indicator)
		return;
	//
	static int width, height;
	m_engine()->GetScreenSize(width, height);

	/*static auto alpha = 1.0f;
	static auto switch_alpha = false;

	if (alpha <= 0.0f || alpha >= 1.0f)
		switch_alpha = !switch_alpha;

	alpha += switch_alpha ? 2.0f * m_globals()->m_frametime : -2.0f * m_globals()->m_frametime;
	alpha = math::clamp(alpha, 0.0f, 1.0f);*/

	auto color = g_cfg.antiaim.flip_indicator_color;
	//color.SetAlpha((int)(min(255.0f * alpha, color.a())));

	render::get().triangle(Vector2D(width / 2, height / 2 + 95), Vector2D(width / 2 - 25, height / 2 + 75), Vector2D(width / 2 + 25, height / 2 + 75), Color(60, 60, 60, 100));
	render::get().triangle(Vector2D(width / 2 - 70, height / 2 + 25), Vector2D(width / 2 - 90, height / 2), Vector2D(width / 2 - 70, height / 2 - 25), Color(60, 60, 60, 100));
	render::get().triangle(Vector2D(width / 2 + 70, height / 2 - 25), Vector2D(width / 2 + 90, height / 2), Vector2D(width / 2 + 70, height / 2 + 25), Color(60, 60, 60, 100));

	if (antiaim::get().manual_side == SIDE_BACK)
	{
		render::get().triangle(Vector2D(width / 2, height / 2 + 95), Vector2D(width / 2 - 25, height / 2 + 75), Vector2D(width / 2 + 25, height / 2 + 75), color);
		render::get().triangle(Vector2D(width / 2 - 70, height / 2 + 25), Vector2D(width / 2 - 90, height / 2), Vector2D(width / 2 - 70, height / 2 - 25), Color(60, 60, 60, 100));
		render::get().triangle(Vector2D(width / 2 + 70, height / 2 - 25), Vector2D(width / 2 + 90, height / 2), Vector2D(width / 2 + 70, height / 2 + 25), Color(60, 60, 60, 100));
	}
	else if (antiaim::get().manual_side == SIDE_LEFT)
	{
		render::get().triangle(Vector2D(width / 2, height / 2 + 95), Vector2D(width / 2 - 25, height / 2 + 75), Vector2D(width / 2 + 25, height / 2 + 75), Color(60, 60, 60, 100));
		render::get().triangle(Vector2D(width / 2 - 70, height / 2 + 25), Vector2D(width / 2 - 90, height / 2), Vector2D(width / 2 - 70, height / 2 - 25), color);
		render::get().triangle(Vector2D(width / 2 + 70, height / 2 - 25), Vector2D(width / 2 + 90, height / 2), Vector2D(width / 2 + 70, height / 2 + 25), Color(60, 60, 60, 100));
	}
	else if (antiaim::get().manual_side == SIDE_RIGHT)
	{
		render::get().triangle(Vector2D(width / 2, height / 2 + 95), Vector2D(width / 2 - 25, height / 2 + 75), Vector2D(width / 2 + 25, height / 2 + 75), Color(60, 60, 60, 100));
		render::get().triangle(Vector2D(width / 2 - 70, height / 2 + 25), Vector2D(width / 2 - 90, height / 2), Vector2D(width / 2 - 70, height / 2 - 25), Color(60, 60, 60, 100));
		render::get().triangle(Vector2D(width / 2 + 70, height / 2 - 25), Vector2D(width / 2 + 90, height / 2), Vector2D(width / 2 + 70, height / 2 + 25), color);
	}
}

void misc::aimbot_hitboxes()
{
	if (!g_cfg.player.enable)
		return;

	if (!g_cfg.player.lag_hitbox)
		return;

	auto player = (player_t*)m_entitylist()->GetClientEntity(aim::get().last_target_index);

	if (!player)
		return;

	auto model = player->GetModel(); //-V807

	if (!model)
		return;

	auto studio_model = m_modelinfo()->GetStudioModel(model);

	if (!studio_model)
		return;

	auto hitbox_set = studio_model->pHitboxSet(player->m_nHitboxSet());

	if (!hitbox_set)
		return;

	for (auto i = 0; i < hitbox_set->numhitboxes; i++)
	{
		auto hitbox = hitbox_set->pHitbox(i);

		if (!hitbox)
			continue;

		if (hitbox->radius == -1.0f) //-V550
			continue;

		auto min = ZERO;
		auto max = ZERO;

		math::vector_transform(hitbox->bbmin, aim::get().last_target[aim::get().last_target_index].record.matrixes_data.main[hitbox->bone], min);
		math::vector_transform(hitbox->bbmax, aim::get().last_target[aim::get().last_target_index].record.matrixes_data.main[hitbox->bone], max);

		m_debugoverlay()->AddCapsuleOverlay(min, max, hitbox->radius, g_cfg.player.lag_hitbox_color.r(), g_cfg.player.lag_hitbox_color.g(), g_cfg.player.lag_hitbox_color.b(), g_cfg.player.lag_hitbox_color.a(), 4.0f, 0, 1);
	}
}

void misc::ragdolls()
{
	if (!g_cfg.misc.ragdolls)
		return;

	for (auto i = 1; i <= m_entitylist()->GetHighestEntityIndex(); ++i)
	{
		auto e = static_cast<entity_t*>(m_entitylist()->GetClientEntity(i));

		if (!e)
			continue;

		if (e->IsDormant())
			continue;

		auto client_class = e->GetClientClass();

		if (!client_class)
			continue;

		if (client_class->m_ClassID != CCSRagdoll)
			continue;

		auto ragdoll = (ragdoll_t*)e;
		ragdoll->m_vecForce().z = 800000.0f;
	}
}

void misc::rank_reveal()
{
	if (!g_cfg.misc.rank_reveal)
		return;

	using RankReveal_t = bool(__cdecl*)(int*);
	static auto Fn = (RankReveal_t)(util::FindSignature(crypt_str("client.dll"), crypt_str("55 8B EC 51 A1 ? ? ? ? 85 C0 75 37")));

	int array[3] =
	{
		0,
		0,
		0
	};

	Fn(array);
}

void misc::fast_stop(CUserCmd* m_pcmd)
{
	if (!g_cfg.misc.fast_stop)
		return;

	if (!(g_ctx.local()->m_fFlags() & FL_ONGROUND && engineprediction::get().backup_data.flags & FL_ONGROUND))
		return;

	auto pressed_move_key = m_pcmd->m_buttons & IN_FORWARD || m_pcmd->m_buttons & IN_MOVELEFT || m_pcmd->m_buttons & IN_BACK || m_pcmd->m_buttons & IN_MOVERIGHT || m_pcmd->m_buttons & IN_JUMP;

	if (pressed_move_key)
		return;

	if (!((antiaim::get().type == g_cfg.antiaim.desync) && (antiaim::get().type == !g_cfg.antiaim.lby_type) && (!g_ctx.globals.weapon->is_grenade() || g_cfg.esp.on_click & !(m_pcmd->m_buttons & IN_ATTACK) && !(m_pcmd->m_buttons & IN_ATTACK2))) || antiaim::get().condition(m_pcmd)) //-V648
	{
		auto velocity = g_ctx.local()->m_vecVelocity();

		if (velocity.Length2D() > 20.0f)
		{
			Vector direction;
			Vector real_view;

			math::vector_angles(velocity, direction);
			m_engine()->GetViewAngles(real_view);

			direction.y = real_view.y - direction.y;

			Vector forward;
			math::angle_vectors(direction, forward);

			static auto cl_forwardspeed = m_cvar()->FindVar(crypt_str("cl_forwardspeed"));
			static auto cl_sidespeed = m_cvar()->FindVar(crypt_str("cl_sidespeed"));

			auto negative_forward_speed = -cl_forwardspeed->GetFloat();
			auto negative_side_speed = -cl_sidespeed->GetFloat();

			auto negative_forward_direction = forward * negative_forward_speed;
			auto negative_side_direction = forward * negative_side_speed;

			m_pcmd->m_forwardmove = negative_forward_direction.x;
			m_pcmd->m_sidemove = negative_side_direction.y;
		}
	}
	else
	{
		auto velocity = g_ctx.local()->m_vecVelocity();

		if (velocity.Length2D() > 20.0f)
		{
			Vector direction;
			Vector real_view;

			math::vector_angles(velocity, direction);
			m_engine()->GetViewAngles(real_view);

			direction.y = real_view.y - direction.y;

			Vector forward;
			math::angle_vectors(direction, forward);

			static auto cl_forwardspeed = m_cvar()->FindVar(crypt_str("cl_forwardspeed"));
			static auto cl_sidespeed = m_cvar()->FindVar(crypt_str("cl_sidespeed"));

			auto negative_forward_speed = -cl_forwardspeed->GetFloat();
			auto negative_side_speed = -cl_sidespeed->GetFloat();

			auto negative_forward_direction = forward * negative_forward_speed;
			auto negative_side_direction = forward * negative_side_speed;

			m_pcmd->m_forwardmove = negative_forward_direction.x;
			m_pcmd->m_sidemove = negative_side_direction.y;
		}
		else
		{
			auto speed = 1.01f;

			if (m_pcmd->m_buttons & IN_DUCK || g_ctx.globals.fakeducking)
				speed *= 2.94117647f;

			static auto switch_move = false;

			if (switch_move)
				m_pcmd->m_sidemove += speed;
			else
				m_pcmd->m_sidemove -= speed;

			switch_move = !switch_move;
		}
	}
}

void misc::backgrounds()
{
	if (g_cfg.misc.background && g_cfg.misc.force_background)
	{
		switch (g_cfg.misc.background)
		{
		case 0: //rain
			/*#define min(x,y) ((x)<(y)?x:y)
#define wh(a) ImColor(1.f,1.f,1.f,a)
void FX(ImDrawList* d, ImVec2 a, ImVec2 b, ImVec2 sz, ImVec2, float t)
{
	static float fl;
	if ((rand() % 500) == 0) fl = t;
	if ((t-fl) > 0)
	{
		auto ft = 0.25f;
		d->AddRectFilled(a, b, wh((ft - (t - fl)) / ft));
	}

	for (int i = 0; i < 2000; ++i) {
		unsigned h = ImGui::GetID(d+i + int(t/4));
		auto f = fmodf(t + fmodf(h / 777.f, 99), 99);
		auto tx = h % (int)sz.x;
		auto ty = h % (int)sz.y;
		if (f < 1) {
			auto py = ty - 1000 * (1 - f);
			d->AddLine({ a.x + tx, a.y + py }, { a.x + tx, a.y + min(py + 10,ty) }, (ImU32)-1);
		}
		else if (f < 1.2f)
			d->AddCircle({ a.x + tx, a.y + ty }, (f - 1) * 10 + h % 5, wh(1-(f-1)*5.f));
	}
}*/
			break;
		case 1: //matrix
			/*#define V2 ImVec2
void FX(ImDrawList*d,V2 a,V2,V2 sz,ImVec4,float t)
{
  static struct{int y,h,c; float t,s;} m[40]={0};
  static int S=0x1234;
  static float t0=t;
  float ZI=t*.07f,Z=ZI+1.f;
  for(int x=0;x<40;x++)
  {
	auto& M=m[x];
	int i=x>=15&&x<25;
	if(M.s==0.f||M.y>16)
	{
	  M.h = (t<7.f||i)*((int)(2+t*.5f) + S%(int)(6+(t*0.3f)));
	  M.y = (M.s==0.f)*-(S%15)-M.h;
	  M.c += S;
	  M.s = (5+(S%14))*(.01f-t*.001f);
	  if(t>5.f&&i)
	  {
		M.c = (340003872375972UL>>(x*5-75))&31;
		M.h = i?(x!=19):0;
	  }
	}
	if((M.t-=t-t0)<0.f)
	{
	  if(t<6.f||!i||M.y!=6)
		M.y++;
	  M.t += M.s;
	}
	char c=64|M.c%42;
	for(int j=0; j<M.h; j++,c=64|(c^M.c+M.h^j)%42)
	  for(int f=(j+1==M.h)?13:4+(M.c&1);f--;)
		d->AddText(0, 13*(i?Z:-Z), V2(a.x-(sz.x*.5f*ZI)+x*8*Z+sin(j+t*f), a.y-(sz.y*.5f*ZI)+(M.y+j)*13*Z+cos(x*f-t)), 0x3c68bb5b, &c, &c+1);
	S|=((S&1)^((S&8)>>2))<<16;
	S>>=1;
  }
  t0 = t;
}*/
			break;
		case 2: //landscape
			/*#define V ImVec2
#define F float
#define D 2048
F m[D*D],I,O,w,x,y,z,h,u,v,l;int q,i,j,T,M;F&A(int x,int y){return m[(x&(D-1))+(y&(D-1))*D];}
F S(F x,F y){I=A(x*D,y*D);return 1-I*I*9;}
void L(F& x,F a,F c){x=sqrt(1.-exp(-a*I*(1.-O)-c*O));}
#define R ((rand()%98)/49.-1)*l
void FX(ImDrawList*d,V a,V b,V B,ImVec4 o,F t){
if(!q){q=1;m[0]=0;l=.5;
for(T=D;T>1;l=l/2,T=T/2){M=T/2;for(j=0;j<D;j+=T){for(i=0;i<D;i+=T){w=A(i,j);x=A(i+T,j);y=A(i,j+T);z=A(i+T,j+T);
A(i+M,j)=(w+x)/2+R;A(i+M,j+T)=(y+z)/2+R;A(i,j+M)=(w+y)/2+R;A(i+T,j+M)=(x+z)/2+R;A(i+M,j+M)=(w+x+y+z)/4+R;}}}}
V s=a,e=b;o.w=1;for(i=64;i--;){s.y=e.y;e.y=a.y+B.y*i/150;d->AddRectFilled(s,e,0xffff6000+i*771);}
for(i=0;i<B.x;i++){s.x=e.x=a.x+i;e.y=s.y=b.y;w=(i/B.x)*2-1;h=S(.5,t*.2)-.5;
for(j=0;j<400;j++){z=j/400.;z=z*z*500;x=w*z;u=x/300+.5;v=z/300+t*.2;l=S(u,v);y=(l-h)*32;s.y=a.y+B.y*(y/(z+.1)+.25);
if(s.y<e.y){I=l-S(u+.01,v+.005)+.01;I=I*(I>0)*30+.2;O=1.0-exp(-z*3e-4);L(o.x,.6,2);L(o.y,.25,4);L(o.z,.15,10);d->AddLine(s,e,ImColor(o));e.y=s.y;}}}}
*/
			break;
		case 3: //quicksort
/*#define V2 ImVec2
#include <vector>
#include <array>
			using namespace std;
			int N = 64, S, J;
#define V vector<int>
			V v = [] {
				V r;
				for (; J < N; J++) r.push_back(rand() % 180);
				return r;
			}();
			vector<array<int, 4>> st{ { 0, N - 1, 0, 0} };
#define A st.back()[0]
#define B st.back()[1]
#define I st.back()[2]
			void FX(ImDrawList * d, V2 a, V2 b, V2 s, ImVec4, float t)
			{
				float bs = s.x / N, y, c;
				for (int i = 0; i < N; i++) {
					y = a.y + v[i];
					c = 70 + v[i];
					d->AddRectFilled(V2(a.x + bs * i, y), V2(a.x + bs * (i + 1), b.y), IM_COL32(c, 255 - c, 255, 255));
				}
				d->AddText(a, -1u, "Quicksort");
				if (st.empty()) return;
				d->AddRect(V2(a.x + bs * A, a.y), V2(a.x + bs * (B + 1), b.y), 0xFF00FF00, 8, ImDrawCornerFlags_Top, 2);
				switch (S) {
				case 0:case 5: if (A >= B)st.pop_back(), S += 3; else I = J = A, S++; break;
				case 1:case 6:
					if (v[J] > v[B])swap(v[I], v[J]), I++;
					if (++J > B)swap(v[I], v[B]), S++;
					break;
				case 2:case 7:st.push_back({ A,I - 1,A,3 }); S = 0; break;
				case 3:st.push_back({ I + 1,B,A,8 }); S = 5; break;
				case 8:S = st.back()[3]; st.pop_back();
				}
			}*/
			break;
		case 4: //blogosphere
/*#define V2 ImVec2
#include <vector>
			int N = 300;
			auto v = [] {
				std::vector<std::pair<V2, V2>>r(N);
				for (auto& p : r)
					p.second = p.first = V2(rand() % 320, rand() % 180);
				return r;
			}();
			float l2(V2 x) { return x.x * x.x + x.y * x.y; }
			void FX(ImDrawList * d, V2 a, V2 b, V2 s, ImVec4, float t)
			{
				float D, T;
				for (auto& p : v) {
					D = sqrt(l2(p.first - p.second));
					if (D > 0) p.first += (p.second - p.first) / D;
					if (D < 4) p.second = V2(rand() % 320, rand() % 180);
				}
				for (int i = 0; i < N; i++) {
					for (int j = i + 1; j < N; j++) {
						D = l2(v[i].first - v[j].first);
						T = l2((v[i].first + v[j].first) - s) / 200;
						if (T > 255) T = 255;
						if (D < 400) d->AddLine(a + v[i].first, a + v[j].first, IM_COL32(T, 255 - T, 255, 70), 2);
					}
				}
			}*/
			break;
		case 5: //dots
/*#define V ImVec2
#define CF d->AddCircleFilled
#define RAND(a) (float)rand()/(float)(RAND_MAX/a)
void FX(ImDrawList*d,V a,V b,V s,ImVec4 m,float t) {
 static bool o = true;
 static V bs[1000];
 if(o){
  o=false;
  for(int i=0;i<1000;++i){
   float g=RAND(IM_PI/2)+(IM_PI/4);
   float r=RAND(50)+5;
   bs[i]=V(g,r);
  }
 }
 for(int i=0;i<1000;++i){
  float
   g=bs[i].x,
   r=bs[i].y;
  r+=sin(t+i)*100;
  CF(V(r*cos(g),r*sin(g))+(s/2+a)+V(r*cos(t),0),i%2+1,IM_COL32(r+100,50,fabs(r)+100,200));
 }
}*/
			break;
		}
	}
	else if (g_cfg.misc.background && !g_cfg.misc.force_background)
	{
		switch (g_cfg.misc.background)
		{
		case 0: //rain
			break;
		case 1: //matrix
			break;
		case 2: //landscape
			break;
		case 3: //quicksort
			break;
		case 4: //blogosphere
			break;
		case 5: //dots
			break;
		}
	}

}

void misc::minigames()
{
	if (g_cfg.misc.minigames)
	{
		switch (g_cfg.misc.minigames)
		{
		case 0: //snake
			break;
		case 1: //tetris
			break;
		case 2: //pacman
			break;
		}
	}
}

void misc::spectators_list()
{
	if (!g_cfg.misc.spectators_list)
		return;

	std::vector <std::string> spectators;

	for (int i = 1; i < m_globals()->m_maxclients; i++)
	{
		auto e = static_cast<player_t*>(m_entitylist()->GetClientEntity(i));

		if (!e)
			continue;

		if (e->is_alive())
			continue;

		if (e->IsDormant())
			continue;

		if (e->m_hObserverTarget().Get() != g_ctx.local())
			continue;

		player_info_t player_info;
		m_engine()->GetPlayerInfo(i, &player_info);

		spectators.push_back(player_info.szName);
	}

	int width, height;
	m_engine()->GetScreenSize(width, height);

	auto x = 100; //-V106
	auto y = 16;

	//background
	render::get().rect_filled(g_cfg.misc.spec_x - 200, y - 100 + g_cfg.misc.spec_y, 200, 20, Color(25, 25, 25, 255));

	//line on top
	render::get().gradient(g_cfg.misc.spec_x - 200, y - 100 + g_cfg.misc.spec_y, 200, 2.5, Color(113, 13, 219, 255), Color(113, 13, 219, 0), GRADIENT_HORIZONTAL);

	//line on bottom
	render::get().gradient(g_cfg.misc.spec_x - 200, y - 80 + g_cfg.misc.spec_y, 200, 2.5, Color(113, 13, 219, 0), Color(113, 13, 219, 255), GRADIENT_HORIZONTAL);

	//line on left
	render::get().gradient(g_cfg.misc.spec_x - 200, y - 100 + g_cfg.misc.spec_y, 2.5, 20, Color(113, 13, 219, 255), Color(113, 13, 219, 0), GRADIENT_VERTICAL);

	//line on right
	render::get().gradient(g_cfg.misc.spec_x, y - 100 + g_cfg.misc.spec_y, 2.5, 22, Color(113, 13, 219, 0), Color(113, 13, 219, 255), GRADIENT_VERTICAL);

	//text
	render::get().text(fonts[KEYBINDS], g_cfg.misc.spec_x - 150, y - 100 + g_cfg.misc.spec_y, Color::White, HFONT_CENTERED_NONE, "Spectators");

	for (auto i = 0; i < spectators.size(); i++)
	{
		int width, height;
		m_engine()->GetScreenSize(width, height);

		auto x = 100;
		auto y = i * 16;

		//render::get().text(fonts[LOGS], width - x, y - 100 + heigth / 2, Color::White, HFONT_CENTERED_NONE, spectators.at(i).c_str()); //-V106

		render::get().text(fonts[KEYBINDS1], g_cfg.misc.spec_x - 190, y - 62 + g_cfg.misc.spec_y, Color::White, HFONT_CENTERED_NONE, spectators.at(i).c_str()); //-V106

	}
}


bool misc::can_shift_shot(int ticks)
{
	if (!g_ctx.local() || !g_ctx.local()->m_hActiveWeapon())
		return false;

	auto tickbase = g_ctx.local()->m_nTickBase();
	auto curtime = m_globals()->m_intervalpertick * (tickbase - ticks);

	if (curtime < g_ctx.local()->m_flNextAttack())
		return false;

	if (curtime < g_ctx.local()->m_hActiveWeapon()->m_flNextPrimaryAttack())
		return false;

	return true;
}

bool misc::double_tap(CUserCmd* m_pcmd)
{
	double_tap_enabled = true;

	static auto recharge_double_tap = false;
	//static auto last_double_tap = 0;
	auto max_tickbase_shift = m_gamerules()->m_bIsValveDS() ? 6 : 15;
	auto tickbase_shift = min(g_ctx.globals.weapon->get_max_tickbase_shift(), max_tickbase_shift);

	if (recharge_double_tap)
	{
		recharge_double_tap = false;
		recharging_double_tap = true;
		g_ctx.globals.ticks_allowed = 0;
		g_ctx.globals.next_tickbase_shift = 0;
		return false;
	}

	if (recharging_double_tap)
	{
		auto recharge_time = g_ctx.globals.weapon->can_double_tap() ? TIME_TO_TICKS(0.5f) : TIME_TO_TICKS(1.0f);

		if (!aim::get().should_stop && can_shift_shot(tickbase_shift))
		{
			recharging_double_tap = false;
			double_tap_key = true;
		}
	}

	if (!g_cfg.ragebot.enable)
	{
		double_tap_enabled = false;
		double_tap_key = false;
		g_ctx.globals.ticks_allowed = 0;
		g_ctx.globals.next_tickbase_shift = 0;
		return false;
	}

	if (!g_cfg.ragebot.double_tap)
	{
		double_tap_enabled = false;
		double_tap_key = false;
		g_ctx.globals.ticks_allowed = 0;
		g_ctx.globals.next_tickbase_shift = 0;
		return false;
	}

	if (g_cfg.ragebot.double_tap_key.key <= KEY_NONE || g_cfg.ragebot.double_tap_key.key >= KEY_MAX)
	{
		double_tap_enabled = false;
		double_tap_key = false;
		g_ctx.globals.ticks_allowed = 0;
		g_ctx.globals.next_tickbase_shift = 0;
		return false;
	}

	if (double_tap_key && g_cfg.ragebot.double_tap_key.key != g_cfg.antiaim.hide_shots_key.key)
		hide_shots_key = false;

	if (!double_tap_key)
	{
		double_tap_enabled = false;
		g_ctx.globals.ticks_allowed = 0;
		g_ctx.globals.next_tickbase_shift = 0;
		return false;
	}

	if (g_ctx.local()->m_bGunGameImmunity() || g_ctx.local()->m_fFlags() & FL_FROZEN)
	{
		double_tap_enabled = false;
		g_ctx.globals.ticks_allowed = 0;
		g_ctx.globals.next_tickbase_shift = 0;
		return false;
	}

	if (m_gamerules()->m_bIsValveDS())
	{
		double_tap_enabled = false;
		g_ctx.globals.ticks_allowed = 0;
		g_ctx.globals.next_tickbase_shift = 0;
		return false;
	}

	if (g_ctx.globals.fakeducking)
	{
		double_tap_enabled = false;
		g_ctx.globals.ticks_allowed = 0;
		g_ctx.globals.next_tickbase_shift = 0;
		return false;
	}

	if (antiaim::get().freeze_check)
		return true;

	if (!g_ctx.globals.weapon->is_grenade() && g_ctx.globals.weapon->m_iItemDefinitionIndex() != WEAPON_TASER && g_ctx.globals.weapon->m_iItemDefinitionIndex() != WEAPON_REVOLVER && !g_ctx.globals.weapon->is_knife() && g_ctx.send_packet && m_pcmd->m_buttons & IN_ATTACK) //-V648
	{
		auto next_command_number = m_pcmd->m_command_number + 1;
		auto user_cmd = m_input()->GetUserCmd(next_command_number);

		memcpy(user_cmd, m_pcmd, sizeof(CUserCmd));
		user_cmd->m_command_number = next_command_number;

		g_ctx.globals.teleport_cmd = user_cmd;
		g_ctx.globals.should_teleport = true;
		util::copy_command(user_cmd, tickbase_shift);

		if (g_ctx.globals.aimbot_working)
		{
			g_ctx.globals.double_tap_aim = true;
			g_ctx.globals.double_tap_aim_check = true;
		}

		recharge_double_tap = true;
		double_tap_enabled = false;
		double_tap_key = false;

		//last_double_tap = g_ctx.globals.fixed_tickbase;
	}
	else if (!g_ctx.globals.weapon->is_grenade() && g_ctx.globals.weapon->m_iItemDefinitionIndex() != WEAPON_TASER && !g_ctx.globals.weapon->is_knife() && g_ctx.globals.weapon->m_iItemDefinitionIndex() != WEAPON_REVOLVER)
		g_ctx.globals.tickbase_shift = tickbase_shift;

	return true;
}

void misc::hide_shots(CUserCmd* m_pcmd, bool should_work)
{
	hide_shots_enabled = true;

	if (!g_cfg.ragebot.enable)
	{
		hide_shots_enabled = false;
		hide_shots_key = false;

		if (should_work)
		{
			g_ctx.globals.ticks_allowed = 0;
			g_ctx.globals.next_tickbase_shift = 0;
		}

		return;
	}

	if (!g_cfg.antiaim.hide_shots)
	{
		hide_shots_enabled = false;
		hide_shots_key = false;

		if (should_work)
		{
			g_ctx.globals.ticks_allowed = 0;
			g_ctx.globals.next_tickbase_shift = 0;
		}

		return;
	}

	if (g_cfg.antiaim.hide_shots_key.key <= KEY_NONE || g_cfg.antiaim.hide_shots_key.key >= KEY_MAX)
	{
		hide_shots_enabled = false;
		hide_shots_key = false;

		if (should_work)
		{
			g_ctx.globals.ticks_allowed = 0;
			g_ctx.globals.next_tickbase_shift = 0;
		}

		return;
	}

	if (!should_work && double_tap_key)
	{
		hide_shots_enabled = false;
		hide_shots_key = false;
		return;
	}

	if (!hide_shots_key)
	{
		hide_shots_enabled = false;
		g_ctx.globals.ticks_allowed = 0;
		g_ctx.globals.next_tickbase_shift = 0;
		return;
	}

	double_tap_key = false;

	if (g_ctx.local()->m_bGunGameImmunity() || g_ctx.local()->m_fFlags() & FL_FROZEN)
	{
		hide_shots_enabled = false;
		g_ctx.globals.ticks_allowed = 0;
		g_ctx.globals.next_tickbase_shift = 0;
		return;
	}

	if (g_ctx.globals.fakeducking)
	{
		hide_shots_enabled = false;
		g_ctx.globals.ticks_allowed = 0;
		g_ctx.globals.next_tickbase_shift = 0;
		return;
	}

	if (antiaim::get().freeze_check)
		return;

	g_ctx.globals.next_tickbase_shift = m_gamerules()->m_bIsValveDS() ? 6 : 9;

	auto revolver_shoot = g_ctx.globals.weapon->m_iItemDefinitionIndex() == WEAPON_REVOLVER && !g_ctx.globals.revolver_working && (m_pcmd->m_buttons & IN_ATTACK || m_pcmd->m_buttons & IN_ATTACK2);
	auto weapon_shoot = m_pcmd->m_buttons & IN_ATTACK && g_ctx.globals.weapon->m_iItemDefinitionIndex() != WEAPON_REVOLVER || m_pcmd->m_buttons & IN_ATTACK2 && g_ctx.globals.weapon->is_knife() || revolver_shoot;

	if (g_ctx.send_packet && !g_ctx.globals.weapon->is_grenade() && weapon_shoot)
		g_ctx.globals.tickbase_shift = g_ctx.globals.next_tickbase_shift;
}