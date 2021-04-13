// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "other_esp.h"
#include "..\autowall\autowall.h"
#include "..\ragebot\antiaim.h"
#include "..\misc\logs.h"
#include "..\misc\misc.h"
#include "..\lagcompensation\local_animations.h"
#include "..\misc\logs.h"

bool can_penetrate(weapon_t* weapon)
{
	auto weapon_info = weapon->get_csweapon_info();

	if (!weapon_info)
		return false;

	Vector view_angles;
	m_engine()->GetViewAngles(view_angles);

	Vector direction;
	math::angle_vectors(view_angles, direction);

	CTraceFilter filter;
	filter.pSkip = g_ctx.local();

	trace_t trace;
	util::trace_line(g_ctx.globals.eye_pos, g_ctx.globals.eye_pos + direction * weapon_info->flRange, MASK_SHOT_HULL | CONTENTS_HITBOX, &filter, &trace);

	if (trace.fraction == 1.0f) //-V550
		return false;

	auto eye_pos = g_ctx.globals.eye_pos;
	auto hits = 1;
	auto damage = (float)weapon_info->iDamage;
	auto penetration_power = weapon_info->flPenetration;

	static auto damageReductionBullets = m_cvar()->FindVar(crypt_str("ff_damage_reduction_bullets"));
	static auto damageBulletPenetration = m_cvar()->FindVar(crypt_str("ff_damage_bullet_penetration"));

	return autowall::get().handle_bullet_penetration(weapon_info, trace, eye_pos, direction, hits, damage, penetration_power, damageReductionBullets->GetFloat(), damageBulletPenetration->GetFloat());
}

void otheresp::penetration_reticle()
{
	if (!g_cfg.player.enable)
		return;

	if (!g_cfg.esp.penetration_reticle)
		return;

	if (!g_ctx.local()->is_alive())
		return;

	auto weapon = g_ctx.local()->m_hActiveWeapon().Get();

	if (!weapon)
		return;

	const auto m_flWeaponInfo = (weapon->get_csweapon_info());

	if (!m_flWeaponInfo)
		return;

	auto color = Color(255, 23, 38, 200);
	if (!weapon->is_non_aim() && weapon->m_iItemDefinitionIndex() != WEAPON_TASER && can_penetrate(weapon))
		color = Color(49, 235, 59, 200);

	static int width, height;
	m_engine()->GetScreenSize(width, height);

	CGameTrace enterTrace;
	CTraceFilter filter;
	Ray_t ray;

	Vector viewangles; m_engine()->GetViewAngles(viewangles);
	Vector direction; math::angle_vectors(viewangles, direction);
	Vector start = g_ctx.globals.eye_pos;
	auto m_flMaxRange = m_flWeaponInfo->flRange * 2; //
	Vector end = start + (direction * m_flMaxRange);
	// u can just use your cheat traceline 
	filter.pSkip = g_ctx.local();
	ray.Init(start, end);
	m_trace()->TraceRay(ray, MASK_SHOT | CONTENTS_GRATE, &filter, &enterTrace);


	float angle_z = math::dot_product(Vector(0, 0, 1), enterTrace.plane.normal);
	float invangle_z = math::dot_product(Vector(0, 0, -1), enterTrace.plane.normal);
	float angle_y = math::dot_product(Vector(0, 1, 0), enterTrace.plane.normal);
	float invangle_y = math::dot_product(Vector(0, -1, 0), enterTrace.plane.normal);
	float angle_x = math::dot_product(Vector(1, 0, 0), enterTrace.plane.normal);
	float invangle_x = math::dot_product(Vector(-1, 0, 0), enterTrace.plane.normal);


	//render::get().rounded_box(width / 2 - 7, height / 2 - 7, 15, 15, 50, 5, color);

	if (angle_z > 0.5 || invangle_z > 0.5)
		render::get().DrawFilled3DBox(enterTrace.endpos, 10, 10, color, color);
	else if (angle_y > 0.5 || invangle_y > 0.5)
		render::get().DrawFilled3DBox(enterTrace.endpos, 10, 10, color, color);
	else if (angle_x > 0.5 || invangle_x > 0.5)
		render::get().DrawFilled3DBox(enterTrace.endpos, 10, 10, color, color);
}

void otheresp::draw_indicators()
{
	if (!g_cfg.esp.indicators)
		return;

	if (!g_ctx.local()->is_alive())
		return;

	static int width, height;
	m_engine()->GetScreenSize(width, height);

	int offset = 1;

	//mindmg 
	if (key_binds::get().get_key_bind_state(4 + g_ctx.globals.current_weapon))
	{
		int override_damage = g_cfg.ragebot.weapon->minimum_override_damage;

		std::string override_dmg = "DMG: " + std::to_string(override_damage);

		render::get().text(fonts[INDICATOR], width / 2 + 10, height / 2 - 15, Color(252, 119, 3, 255), HFONT_CENTERED_NONE, override_dmg.c_str());
	}

	//doubletap
	if (misc::get().double_tap_enabled || misc::get().recharging_double_tap)
	{
		render::get().text(fonts[INDICATOR], width / 2, height / 2 + 15 * offset, misc::get().recharging_double_tap ? Color(255, 55, 33, 255) : Color(36, 252, 3, 255), HFONT_CENTERED_NONE, "DT");
		offset = offset + 1;
	}

	//hideshots
	if (misc::get().hide_shots_enabled)
	{
		render::get().text(fonts[INDICATOR], width / 2, height / 2 + 15 * offset, Color(22, 106, 250, 255), HFONT_CENTERED_NONE, "HS");
		offset = offset + 1;
	}

	//safepoints
	if (key_binds::get().get_key_bind_state(3))
	{
		render::get().text(fonts[INDICATOR], width / 2, height / 2 + 15 * offset, Color(36, 252, 3, 255), HFONT_CENTERED_NONE, "SP");
		offset = offset + 1;
	}

	//baim
	if (key_binds::get().get_key_bind_state(22))
	{
		render::get().text(fonts[INDICATOR], width / 2, height / 2 + 15 * offset, Color(36, 252, 3, 255), HFONT_CENTERED_NONE, "BAIM");
		offset = offset + 1;
	}

	//fakeduck
	if (key_binds::get().get_key_bind_state(20))
	{
		render::get().text(fonts[INDICATOR], width / 2, height / 2 + 15 * offset, Color(0, 46, 230, 255), HFONT_CENTERED_NONE, "FD");
		offset = offset + 1;
	}

	//auto peek
	if (key_binds::get().get_key_bind_state(18))
	{
		render::get().text(fonts[INDICATOR], width / 2, height / 2 + 15 * offset, Color(230, 168, 0, 255), HFONT_CENTERED_NONE, "AP");
		offset = offset + 1;
	}

	//Invert
	if (key_binds::get().get_key_bind_state(16))
	{
		render::get().text(fonts[INDICATOR], width / 2, height / 2 + 15 * offset, Color(22, 106, 250, 255), HFONT_CENTERED_NONE, "INVERT");
		offset = offset + 1;
	}
}

void otheresp::draw_binds()
{
	if (!g_cfg.misc.draw_keys)
		return;

	static int width, height;

	m_engine()->GetScreenSize(width, height);

	int x{ 15 };
	int offset = 1;

	// overlays 
	//render::get().rounded_box(x + 10, height / 2 + 10, 200, 5 + 15 * offset, 25, 10, Color(10, 10, 10, 160));
	// line.
	//render::get().gradient(x + 13.5, height / 2 + 10, 192, 2, Color(3, 144, 252, 230), Color(151, 41, 255, 230), GRADIENT_HORIZONTAL);
	// text.
	//render::get().text(fonts[KEYBINDS], x + 10 + 60, height / 2 + 10.5, { 255, 255, 255, 255 }, HFONT_CENTERED_NONE, "Keybinds");

	//background
	render::get().rect_filled(g_cfg.misc.key_x + 10, g_cfg.misc.key_y + 9, 200, 5 + 15 * offset, Color(25, 25, 25, 255));

	//line on top
	render::get().gradient(g_cfg.misc.key_x + 10, g_cfg.misc.key_y + 9, 200, 2.5, Color(113, 13, 219, 255), Color(113, 13, 219, 0), GRADIENT_HORIZONTAL);

	//line on bottom
	render::get().gradient(g_cfg.misc.key_x + 10, g_cfg.misc.key_y + 29, 200, 2.5, Color(113, 13, 219, 0), Color(113, 13, 219, 255), GRADIENT_HORIZONTAL);

	//line on left
	render::get().gradient(g_cfg.misc.key_x + 10, g_cfg.misc.key_y + 9, 2.5, 20, Color(113, 13, 219, 255), Color(113, 13, 219, 0), GRADIENT_VERTICAL);

	//line on right
	render::get().gradient(g_cfg.misc.key_x + 210, g_cfg.misc.key_y + 11, 2.5, 20, Color(113, 13, 219, 0), Color(113, 13, 219, 255), GRADIENT_VERTICAL);

	//text
	render::get().text(fonts[KEYBINDS], g_cfg.misc.key_x + 10 + 60, g_cfg.misc.key_y + 9.5, { 240, 240, 240, 255 }, HFONT_CENTERED_NONE, "Keybinds");

	// dt
	if (misc::get().double_tap_key)
	{
		render::get().text(fonts[KEYBINDS1], g_cfg.misc.key_x + 10 + 5, g_cfg.misc.key_y + 15 + 15 * offset, { 255, 255, 255, 255 }, HFONT_CENTERED_NONE, "Doubletap");
		render::get().text(fonts[KEYBINDS1], g_cfg.misc.key_x + 10 + 140, g_cfg.misc.key_y + 15 + 15 * offset, { 255, 255, 255, 255 }, HFONT_CENTERED_NONE, "Enabled");
		offset = offset + 1;
	}

	// hs
	if (misc::get().hide_shots_key)
	{
		render::get().text(fonts[KEYBINDS1], g_cfg.misc.key_x + 10 + 5, g_cfg.misc.key_y + 15 + 15 * offset, { 255, 255, 255, 255 }, HFONT_CENTERED_NONE, "Hideshots");
		render::get().text(fonts[KEYBINDS1], g_cfg.misc.key_x + 10 + 140, g_cfg.misc.key_y + 15 + 15 * offset, { 255, 255, 255, 255 }, HFONT_CENTERED_NONE, "Enabled");
		offset = offset + 1;
	}

	//safepoints
	if (key_binds::get().get_key_bind_state(3))
	{
		render::get().text(fonts[KEYBINDS1], g_cfg.misc.key_x + 10 + 5, g_cfg.misc.key_y + 15 + 15 * offset, { 255, 255, 255, 255 }, HFONT_CENTERED_NONE, "Force Safepoints");
		render::get().text(fonts[KEYBINDS1], g_cfg.misc.key_x + 10 + 140, g_cfg.misc.key_y + 15 + 15 * offset, { 255, 255, 255, 255 }, HFONT_CENTERED_NONE, "Enabled");
		offset = offset + 1;
	}

	// mindmg 
	if (key_binds::get().get_key_bind_state(4 + g_ctx.globals.current_weapon))
	{
		render::get().text(fonts[KEYBINDS1], g_cfg.misc.key_x + 10 + 5, g_cfg.misc.key_y + 15 + 15 * offset, { 255, 255, 255, 255 }, HFONT_CENTERED_NONE, "Mindmg Override");
		render::get().text(fonts[KEYBINDS1], g_cfg.misc.key_x + 10 + 140, g_cfg.misc.key_y + 15 + 15 * offset, { 255, 255, 255, 255 }, HFONT_CENTERED_NONE, "Enabled");
		offset = offset + 1;
	}

	// baim
	if (key_binds::get().get_key_bind_state(22))
	{
		render::get().text(fonts[KEYBINDS1], g_cfg.misc.key_x + 10 + 5, g_cfg.misc.key_y + 15 + 15 * offset, { 255, 255, 255, 255 }, HFONT_CENTERED_NONE, "Force baim");
		render::get().text(fonts[KEYBINDS1], g_cfg.misc.key_x + 10 + 140, g_cfg.misc.key_y + 15 + 15 * offset, { 255, 255, 255, 255 }, HFONT_CENTERED_NONE, "Enabled");
		offset = offset + 1;
	}

	// thirdperson
	if (key_binds::get().get_key_bind_state(17))
	{
		render::get().text(fonts[KEYBINDS1], g_cfg.misc.key_x + 10 + 5, g_cfg.misc.key_y + 15 + 15 * offset, { 255, 255, 255, 255 }, HFONT_CENTERED_NONE, "Thirdperson");
		render::get().text(fonts[KEYBINDS1], g_cfg.misc.key_x + 10 + 140, g_cfg.misc.key_y + 15 + 15 * offset, { 255, 255, 255, 255 }, HFONT_CENTERED_NONE, "Enabled");
		offset = offset + 1;
	}

	// slowwalk
	if (key_binds::get().get_key_bind_state(21))
	{
		render::get().text(fonts[KEYBINDS1], g_cfg.misc.key_x + 10 + 5, g_cfg.misc.key_y + 15 + 15 * offset, { 255, 255, 255, 255 }, HFONT_CENTERED_NONE, "Slowwalk");
		render::get().text(fonts[KEYBINDS1], g_cfg.misc.key_x + 10 + 140, g_cfg.misc.key_y + 15 + 15 * offset, { 255, 255, 255, 255 }, HFONT_CENTERED_NONE, "Enabled");
		offset = offset + 1;
	}

	// fakeduck
	if (key_binds::get().get_key_bind_state(20))
	{
		render::get().text(fonts[KEYBINDS1], g_cfg.misc.key_x + 10 + 5, g_cfg.misc.key_y + 15 + 15 * offset, { 255, 255, 255, 255 }, HFONT_CENTERED_NONE, "Fakeduck");
		render::get().text(fonts[KEYBINDS1], g_cfg.misc.key_x + 10 + 140, g_cfg.misc.key_y + 15 + 15 * offset, { 255, 255, 255, 255 }, HFONT_CENTERED_NONE, "Enabled");
		offset = offset + 1;
	}

	// auto peek 
	if (key_binds::get().get_key_bind_state(18))
	{
		render::get().text(fonts[KEYBINDS1], g_cfg.misc.key_x + 10 + 5, g_cfg.misc.key_y + 15 + 15 * offset, { 255, 255, 255, 255 }, HFONT_CENTERED_NONE, "Auto peek");
		render::get().text(fonts[KEYBINDS1], g_cfg.misc.key_x + 10 + 140, g_cfg.misc.key_y + 15 + 15 * offset, { 255, 255, 255, 255 }, HFONT_CENTERED_NONE, "Enabled");
		offset = offset + 1;
	}

	// aa inverter 
	if (key_binds::get().get_key_bind_state(16))
	{
		render::get().text(fonts[KEYBINDS1], g_cfg.misc.key_x + 10 + 5, g_cfg.misc.key_y + 15 + 15 * offset, { 255, 255, 255, 255 }, HFONT_CENTERED_NONE, "AA Inverter");
		render::get().text(fonts[KEYBINDS1], g_cfg.misc.key_x + 10 + 140, g_cfg.misc.key_y + 15 + 15 * offset, { 255, 255, 255, 255 }, HFONT_CENTERED_NONE, "Enabled");
		offset = offset + 1;
	}
}

void otheresp::hitmarker_paint()
{
	if (!g_cfg.esp.hitmarker[0] && !g_cfg.esp.hitmarker[1])
	{
		hitmarker.hurt_time = FLT_MIN;
		hitmarker.point = ZERO;
		return;
	}

	if (!g_ctx.local()->is_alive())
	{
		hitmarker.hurt_time = FLT_MIN;
		hitmarker.point = ZERO;
		return;
	}

	switch (g_cfg.esp.hitmarkers)
	{
	case 0:
		break;
	case 1:
		if (hitmarker.hurt_time + 0.7f > m_globals()->m_curtime)
		{
			if (g_cfg.esp.hitmarker[0])
			{
				static int width, height;
				m_engine()->GetScreenSize(width, height);

				auto alpha = (int)((hitmarker.hurt_time + 0.7f - m_globals()->m_curtime) * 255.0f);
				hitmarker.hurt_color.SetAlpha(alpha);

				auto offset = 7.0f - (float)alpha / 255.0f * 7.0f;
				int screenCenterY, screenCenterX;
				auto lineSize = 15;


				screenCenterX = width / 2;
				screenCenterY = height / 2;

				render::get().line(screenCenterX - lineSize, screenCenterY - lineSize, screenCenterX - (lineSize / 4), screenCenterY - (lineSize / 4), hitmarker.hurt_color);
				render::get().line(screenCenterX - lineSize, screenCenterY + lineSize, screenCenterX - (lineSize / 4), screenCenterY + (lineSize / 4), hitmarker.hurt_color);
				render::get().line(screenCenterX + lineSize, screenCenterY + lineSize, screenCenterX + (lineSize / 4), screenCenterY + (lineSize / 4), hitmarker.hurt_color);
				render::get().line(screenCenterX + lineSize, screenCenterY - lineSize, screenCenterX + (lineSize / 4), screenCenterY - (lineSize / 4), hitmarker.hurt_color);
				render::get().circle(screenCenterX, screenCenterY, 25.f, 7.f, hitmarker.hurt_color);
			}

			if (g_cfg.esp.hitmarker[1])
			{
				Vector world;

				if (math::world_to_screen(hitmarker.point, world))
				{
					auto alpha = (int)((hitmarker.hurt_time + 0.7f - m_globals()->m_curtime) * 255.0f);
					hitmarker.hurt_color.SetAlpha(alpha);

					auto offset = 7.0f - (float)alpha / 255.0f * 7.0f;

					auto linesize = 15;


					render::get().line(world.x - linesize, world.y - linesize, world.x - (linesize / 4), world.y - (linesize / 4), hitmarker.hurt_color);
					render::get().line(world.x - linesize, world.y + linesize, world.x - (linesize / 4), world.y + (linesize / 4), hitmarker.hurt_color);
					render::get().line(world.x + linesize, world.y + linesize, world.x + (linesize / 4), world.y + (linesize / 4), hitmarker.hurt_color);
					render::get().line(world.x + linesize, world.y - linesize, world.x + (linesize / 4), world.y - (linesize / 4), hitmarker.hurt_color);
					render::get().circle(world.x, world.y, 25.f, 7.f, hitmarker.hurt_color);
				}
			}
		}
		break;
	case 2:
		if (hitmarker.hurt_time + 0.7f > m_globals()->m_curtime)
		{
			if (g_cfg.esp.hitmarker[0])
			{
				static int width, height;
				m_engine()->GetScreenSize(width, height);

				auto alpha = (int)((hitmarker.hurt_time + 0.7f - m_globals()->m_curtime) * 255.0f);
				hitmarker.hurt_color.SetAlpha(alpha);

				auto offset = 7.0f - (float)alpha / 255.0f * 7.0f;
				int screenCenterY, screenCenterX;
				auto lineSize = 15;


				screenCenterX = width / 2;
				screenCenterY = height / 2;

				render::get().line(screenCenterX - lineSize, screenCenterY - lineSize, screenCenterX - (lineSize / 4), screenCenterY - (lineSize / 4), hitmarker.hurt_color);
				render::get().line(screenCenterX - lineSize, screenCenterY + lineSize, screenCenterX - (lineSize / 4), screenCenterY + (lineSize / 4), hitmarker.hurt_color);
				render::get().line(screenCenterX + lineSize, screenCenterY + lineSize, screenCenterX + (lineSize / 4), screenCenterY + (lineSize / 4), hitmarker.hurt_color);
				render::get().line(screenCenterX + lineSize, screenCenterY - lineSize, screenCenterX + (lineSize / 4), screenCenterY - (lineSize / 4), hitmarker.hurt_color);
			}

			if (g_cfg.esp.hitmarker[1])
			{
				Vector world;

				if (math::world_to_screen(hitmarker.point, world))
				{
					auto alpha = (int)((hitmarker.hurt_time + 0.7f - m_globals()->m_curtime) * 255.0f);
					hitmarker.hurt_color.SetAlpha(alpha);

					auto offset = 7.0f - (float)alpha / 255.0f * 7.0f;

					auto linesize = 15;


					render::get().line(world.x - linesize, world.y - linesize, world.x - (linesize / 4), world.y - (linesize / 4), hitmarker.hurt_color);
					render::get().line(world.x - linesize, world.y + linesize, world.x - (linesize / 4), world.y + (linesize / 4), hitmarker.hurt_color);
					render::get().line(world.x + linesize, world.y + linesize, world.x + (linesize / 4), world.y + (linesize / 4), hitmarker.hurt_color);
					render::get().line(world.x + linesize, world.y - linesize, world.x + (linesize / 4), world.y - (linesize / 4), hitmarker.hurt_color);
				}
			}
		}
		break;
	case 3:
		if (hitmarker.hurt_time + 0.7f > m_globals()->m_curtime)
		{
			if (g_cfg.esp.hitmarker[0])
			{
				static int width, height;
				m_engine()->GetScreenSize(width, height);

				auto alpha = (int)((hitmarker.hurt_time + 0.7f - m_globals()->m_curtime) * 255.0f);
				hitmarker.hurt_color.SetAlpha(alpha);

				auto offset = 7.0f - (float)alpha / 255.0f * 7.0f;
				int screenCenterY, screenCenterX;
				auto lineSize = 15;


				screenCenterX = width / 2;
				screenCenterY = height / 2;

				render::get().circle(screenCenterX, screenCenterY, 25.f, 7.f, hitmarker.hurt_color);
			}

			if (g_cfg.esp.hitmarker[1])
			{
				Vector world;

				if (math::world_to_screen(hitmarker.point, world))
				{
					auto alpha = (int)((hitmarker.hurt_time + 0.7f - m_globals()->m_curtime) * 255.0f);
					hitmarker.hurt_color.SetAlpha(alpha);

					auto offset = 7.0f - (float)alpha / 255.0f * 7.0f;

					auto linesize = 15;

					render::get().circle(world.x, world.y, 25.f, 7.f, hitmarker.hurt_color);
				}
			}
		}
		break;
	case 4:
		if (hitmarker.hurt_time + 0.7f > m_globals()->m_curtime)
		{
			if (g_cfg.esp.hitmarker[0])
			{
				static int width, height;
				m_engine()->GetScreenSize(width, height);

				auto alpha = (int)((hitmarker.hurt_time + 0.7f - m_globals()->m_curtime) * 255.0f);
				hitmarker.hurt_color.SetAlpha(alpha);

				auto offset = 7.0f - (float)alpha / 255.0f * 7.0f;
				int screenCenterY, screenCenterX;
				auto lineSize = 15;


				screenCenterX = width / 2;
				screenCenterY = height / 2;

				render::get().line(screenCenterX - lineSize, screenCenterY - lineSize, screenCenterX - (lineSize / 4), screenCenterY - (lineSize / 4), hitmarker.hurt_color);
				render::get().line(screenCenterX - lineSize, screenCenterY - lineSize, screenCenterX - (lineSize / 4), screenCenterY + (lineSize / 4), hitmarker.hurt_color);
				render::get().line(screenCenterX + lineSize, screenCenterY + lineSize, screenCenterX + (lineSize / 4), screenCenterY + (lineSize / 4), hitmarker.hurt_color);
				render::get().line(screenCenterX + lineSize, screenCenterY + lineSize, screenCenterX + (lineSize / 4), screenCenterY - (lineSize / 4), hitmarker.hurt_color);

				render::get().line(screenCenterX - lineSize, screenCenterY + lineSize, screenCenterX - (lineSize / 4), screenCenterY - (lineSize / 4), hitmarker.hurt_color);
				render::get().line(screenCenterX - lineSize, screenCenterY + lineSize, screenCenterX - (lineSize / 4), screenCenterY + (lineSize / 4), hitmarker.hurt_color);
				render::get().line(screenCenterX + lineSize, screenCenterY - lineSize, screenCenterX + (lineSize / 4), screenCenterY + (lineSize / 4), hitmarker.hurt_color);
				render::get().line(screenCenterX + lineSize, screenCenterY - lineSize, screenCenterX + (lineSize / 4), screenCenterY - (lineSize / 4), hitmarker.hurt_color);
			}

			if (g_cfg.esp.hitmarker[1])
			{
				Vector world;

				if (math::world_to_screen(hitmarker.point, world))
				{
					auto alpha = (int)((hitmarker.hurt_time + 0.7f - m_globals()->m_curtime) * 255.0f);
					hitmarker.hurt_color.SetAlpha(alpha);

					auto offset = 7.0f - (float)alpha / 255.0f * 7.0f;

					auto linesize = 15;


					render::get().line(world.x - linesize, world.y - linesize, world.x - (linesize / 4), world.y - (linesize / 4), hitmarker.hurt_color);
					render::get().line(world.x - linesize, world.y - linesize, world.x - (linesize / 4), world.y + (linesize / 4), hitmarker.hurt_color);
					render::get().line(world.x + linesize, world.y + linesize, world.x + (linesize / 4), world.y + (linesize / 4), hitmarker.hurt_color);
					render::get().line(world.x + linesize, world.y + linesize, world.x + (linesize / 4), world.y - (linesize / 4), hitmarker.hurt_color);

					render::get().line(world.x - linesize, world.y + linesize, world.x - (linesize / 4), world.y - (linesize / 4), hitmarker.hurt_color);
					render::get().line(world.x - linesize, world.y + linesize, world.x - (linesize / 4), world.y + (linesize / 4), hitmarker.hurt_color);
					render::get().line(world.x + linesize, world.y - linesize, world.x + (linesize / 4), world.y + (linesize / 4), hitmarker.hurt_color);
					render::get().line(world.x + linesize, world.y - linesize, world.x + (linesize / 4), world.y - (linesize / 4), hitmarker.hurt_color);

					render::get().line(world.x - linesize, world.y - linesize, world.x - (linesize / 4), world.y - (linesize / 4), hitmarker.hurt_color);
					render::get().line(world.x - linesize, world.y + linesize, world.x - (linesize / 4), world.y + (linesize / 4), hitmarker.hurt_color);
					render::get().line(world.x + linesize, world.y + linesize, world.x + (linesize / 4), world.y + (linesize / 4), hitmarker.hurt_color);
					render::get().line(world.x + linesize, world.y - linesize, world.x + (linesize / 4), world.y - (linesize / 4), hitmarker.hurt_color);
				}
			}
		}
		break;
	}
}

void otheresp::damage_marker_paint()
{
	for (auto i = 1; i < m_globals()->m_maxclients; i++) //-V807
	{
		if (damage_marker[i].hurt_time + 0.1f > m_globals()->m_curtime)
		{
			Vector screen;

			if (!math::world_to_screen(damage_marker[i].position, screen))
				continue;

			damage_marker[i].hurt_time = g_ctx.local()->m_nTickBase() * m_globals()->m_intervalpertick + 1.f;

			int alpha = 255;

			if (m_globals()->m_curtime - damage_marker[i].LastUpdate > 0.0001f)
			{
				damage_marker[i].position -= (1.f * (m_globals()->m_curtime - damage_marker[i].hurt_time));
				damage_marker[i].LastUpdate = m_globals()->m_curtime;
			}

			if (m_globals()->m_curtime - damage_marker[i].LastUpdate > 0.1f)
				alpha = 0;

			damage_marker[i].hurt_color.SetAlpha(alpha);

			render::get().text(fonts[DAMAGE_MARKER], screen.x, screen.y, damage_marker[i].hurt_color, HFONT_CENTERED_X | HFONT_CENTERED_Y, "%i", damage_marker[i].damage);
		}
	}
}

void draw_circe(float x, float y, float radius, int resolution, DWORD color, DWORD color2, LPDIRECT3DDEVICE9 device);

void otheresp::spread_crosshair(LPDIRECT3DDEVICE9 device)
{
	if (!g_cfg.player.enable)
		return;

	if (!g_cfg.esp.show_spread)
		return;

	if (!g_ctx.local()->is_alive())
		return;

	auto weapon = g_ctx.local()->m_hActiveWeapon().Get();

	if (weapon->is_non_aim())
		return;

	int w, h;
	m_engine()->GetScreenSize(w, h);

	draw_circe((float)w * 0.5f, (float)h * 0.5f, g_ctx.globals.inaccuracy * 500.0f, 50, D3DCOLOR_RGBA(g_cfg.esp.show_spread_color.r(), g_cfg.esp.show_spread_color.g(), g_cfg.esp.show_spread_color.b(), g_cfg.esp.show_spread_color.a()), D3DCOLOR_RGBA(0, 0, 0, 0), device);
}

void draw_circe(float x, float y, float radius, int resolution, DWORD color, DWORD color2, LPDIRECT3DDEVICE9 device)
{
	LPDIRECT3DVERTEXBUFFER9 g_pVB2 = nullptr;
	std::vector <CUSTOMVERTEX2> circle(resolution + 2);

	circle[0].x = x;
	circle[0].y = y;
	circle[0].z = 0.0f;

	circle[0].rhw = 1.0f;
	circle[0].color = color2;

	for (auto i = 1; i < resolution + 2; i++)
	{
		circle[i].x = (float)(x - radius * cos(D3DX_PI * ((i - 1) / (resolution / 2.0f))));
		circle[i].y = (float)(y - radius * sin(D3DX_PI * ((i - 1) / (resolution / 2.0f))));
		circle[i].z = 0.0f;

		circle[i].rhw = 1.0f;
		circle[i].color = color;
	}

	device->CreateVertexBuffer((resolution + 2) * sizeof(CUSTOMVERTEX2), D3DUSAGE_WRITEONLY, D3DFVF_XYZRHW | D3DFVF_DIFFUSE, D3DPOOL_DEFAULT, &g_pVB2, nullptr); //-V107

	if (!g_pVB2)
		return;

	void* pVertices;

	g_pVB2->Lock(0, (resolution + 2) * sizeof(CUSTOMVERTEX2), (void**)&pVertices, 0); //-V107
	memcpy(pVertices, &circle[0], (resolution + 2) * sizeof(CUSTOMVERTEX2));
	g_pVB2->Unlock();

	device->SetTexture(0, nullptr);
	device->SetPixelShader(nullptr);
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	device->SetStreamSource(0, g_pVB2, 0, sizeof(CUSTOMVERTEX2));
	device->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	device->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, resolution);

	g_pVB2->Release();
}

void otheresp::automatic_peek_indicator()
{
	auto weapon = g_ctx.local()->m_hActiveWeapon().Get();

	if (!weapon)
		return;

	static auto position = ZERO;

	if (!g_ctx.globals.start_position.IsZero())
		position = g_ctx.globals.start_position;

	if (position.IsZero())
		return;

	static auto alpha = 0.0f;

	if (key_binds::get().get_key_bind_state(18) || alpha)
	{
		if (key_binds::get().get_key_bind_state(18))
			alpha += 3.0f * m_globals()->m_frametime; //-V807
		else
			alpha -= 3.0f * m_globals()->m_frametime;

		alpha = math::clamp(alpha, 0.0f, 1.0f);
		render::get().Draw3DFilledCircle(position, 20.0f, g_ctx.globals.fired_shot ? Color(149, 43, 255, (int)(alpha * 255.0f)) : Color(255, 255, 255, (int)(alpha * 255.0f)));
		render::get().Draw3DRainbowCircle(position, 3.0f);
		render::get().Draw3DRainbowCircle(position, 20.05f);

		Vector screen;

		if (math::world_to_screen(position, screen))
		{
			static auto offset = 30.0f;

			if (!g_ctx.globals.fired_shot)
			{
				static auto switch_offset = false;

				if (offset <= 30.0f || offset >= 55.0f)
					switch_offset = !switch_offset;

				offset += switch_offset ? 22.0f * m_globals()->m_frametime : -22.0f * m_globals()->m_frametime;
				offset = math::clamp(offset, 30.0f, 55.0f);
			}
		}
	}
}