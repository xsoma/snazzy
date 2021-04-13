// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "configs.h"
#include "base64.h"
#include "..\includes.hpp"
#include "..\utils\util.hpp"
#include <shlobj.h>
#include "../lua/menu_item.h"

std::unordered_map <std::string, float[4]> colors;

C_ConfigManager* cfg_manager = new C_ConfigManager();
Config g_cfg;

item_setting* get_by_definition_index(const int definition_index)
{
	auto it = std::find_if(std::begin(g_cfg.skins.skinChanger), std::end(g_cfg.skins.skinChanger), [definition_index](const item_setting& e)
		{
			return e.itemId == definition_index;
		});

	return it == std::end(g_cfg.skins.skinChanger) ? nullptr : &*it;
}

void C_ConfigManager::setup()
{
	setup_item(&g_cfg.ragebot.enable, false, crypt_str("Ragebot.enable_poop"));
	setup_item(&g_cfg.ragebot.silent_aim, false, crypt_str("Ragebot.silent_aim_e"));
	setup_item(&g_cfg.ragebot.autowall, false, crypt_str("Ragebot.autowall2"));
	setup_item(&g_cfg.ragebot.autoshoot, false, crypt_str("Ragebot.autofire"));
	setup_item(&g_cfg.ragebot.double_tap, false, crypt_str("Ragebot.double_tap2"));
	setup_item(&g_cfg.ragebot.double_tap_key, key_bind(TOGGLE), crypt_str("Ragebot.double_tap_key2"));
	setup_item(&g_cfg.ragebot.autoscope, false, crypt_str("Ragebot.autoscope2"));
	setup_item(&g_cfg.ragebot.safe_point_key, key_bind(HOLD), crypt_str("Ragebot.safe_point_key12"));
	setup_item(&g_cfg.ragebot.body_aim_key, key_bind(HOLD), crypt_str("Ragebot.body_aim_key3"));

	for (auto i = 0; i < 8; i++)
	{
		setup_item(&g_cfg.ragebot.weapon[i].selection_type, 0, std::to_string(i) + crypt_str("Ragebot.selection_types"));
		setup_item(&g_cfg.ragebot.weapon[i].autostop, false, std::to_string(i) + crypt_str("Ragebot_automaticstops"));
		setup_item(&g_cfg.ragebot.weapon[i].autostop_modifiers, 6, std::to_string(i) + crypt_str("Ragebot.autostop_conditionss"));
		setup_item(&g_cfg.ragebot.weapon[i].hitchance, false, std::to_string(i) + crypt_str("Ragebot.hitchances"));
		setup_item(&g_cfg.ragebot.weapon[i].static_point_scale, false, std::to_string(i) + crypt_str("Ragebot.static_point_scalse"));
		setup_item(&g_cfg.ragebot.weapon[i].head_scale, 0.0f, std::to_string(i) + crypt_str("Ragebot.head_scales"));
		setup_item(&g_cfg.ragebot.weapon[i].body_scale, 0.0f, std::to_string(i) + crypt_str("Ragebot.body_scalse"));
		setup_item(&g_cfg.ragebot.weapon[i].hitchance_amount, 1, std::to_string(i) + crypt_str("Ragebot.hitchance_amounts"));
		setup_item(&g_cfg.ragebot.weapon[i].minimum_visible_damage, 1, std::to_string(i) + crypt_str("Ragebot.minimum_visible_damages"));
		setup_item(&g_cfg.ragebot.weapon[i].minimum_damage, 1, std::to_string(i) + crypt_str("Ragebot.minimum_damages"));
		setup_item(&g_cfg.ragebot.weapon[i].damage_override_key, key_bind(HOLD), std::to_string(i) + crypt_str("Ragebot.damage_override_keys"));
		setup_item(&g_cfg.ragebot.weapon[i].minimum_override_damage, 1, std::to_string(i) + crypt_str("Ragebot.minimum_override_damages"));
		setup_item(&g_cfg.ragebot.weapon[i].hitboxes, 9, std::to_string(i) + crypt_str("Ragebot.hitboxess"));
		setup_item(&g_cfg.ragebot.weapon[i].max_misses, false, std::to_string(i) + crypt_str("Ragebot.max_missess"));
		setup_item(&g_cfg.ragebot.weapon[i].max_misses_amount, 0, std::to_string(i) + crypt_str("Ragebot.max_misses_amounts"));
		setup_item(&g_cfg.ragebot.weapon[i].prefer_safe_points, false, std::to_string(i) + crypt_str("Ragebot.prefer_safe_pointss"));
		setup_item(&g_cfg.ragebot.weapon[i].prefer_body_aim, false, std::to_string(i) + crypt_str("Ragebot.prefer_body_aims"));
	}

	setup_item(&g_cfg.antiaim.enable, false, crypt_str("Antiaim.enables"));
	setup_item(&g_cfg.antiaim.antiaim_type, 0, crypt_str("Antiaim.antiaim_types"));
	setup_item(&g_cfg.antiaim.hide_shots, false, crypt_str("Ragebot.hide_shotss"));
	setup_item(&g_cfg.antiaim.hide_shots_key, key_bind(TOGGLE), crypt_str("Ragebot.hide_shots_keys"));
	setup_item(&g_cfg.antiaim.invert_double_tap, false, crypt_str("Antiaim.invert_double_taps"));
	setup_item(&g_cfg.antiaim.invert_after_double_tap, false, crypt_str("Antiaim.invert_after_double_taps"));
	setup_item(&g_cfg.antiaim.desync, 0, crypt_str("Antiaim.desyncs"));
	setup_item(&g_cfg.antiaim.legit_lby_type, 0, crypt_str("Antiaim.legit_lby_types"));
	setup_item(&g_cfg.antiaim.lby_type, 0, crypt_str("Antiaim.lby_types"));
	setup_item(&g_cfg.antiaim.manual_back, key_bind(TOGGLE), crypt_str("Antiaim.manual_backs"));
	setup_item(&g_cfg.antiaim.manual_left, key_bind(TOGGLE), crypt_str("Antiaim.manual_lefts"));
	setup_item(&g_cfg.antiaim.manual_right, key_bind(TOGGLE), crypt_str("Antiaim.manual_rights"));
	setup_item(&g_cfg.antiaim.flip_desync, key_bind(TOGGLE), crypt_str("Antiaim.flip_desyncs"));
	setup_item(&g_cfg.antiaim.flip_indicator, false, crypt_str("Antiaim.flip_indicators"));
	setup_item(&g_cfg.antiaim.flip_indicator_color, Color(255, 255, 255), crypt_str("Antiaim.flip_indicator_colors"));
	setup_item(&g_cfg.antiaim.fakelag, false, crypt_str("Antiaim.fake_lags"));
	setup_item(&g_cfg.antiaim.fakelag_type, 0, crypt_str("Antiaim.fake_lag_types"));
	setup_item(&g_cfg.antiaim.fakelag_enablers, 4, crypt_str("Antiaim.fake_lag_enablerss"));
	setup_item(&g_cfg.antiaim.fakelag_amount, 1, crypt_str("Antiaim.fake_lag_limits"));
	setup_item(&g_cfg.antiaim.triggers_fakelag_amount, 1, crypt_str("Antiaim.triggers_fakelag_limits"));
	setup_item(&g_cfg.antiaim.break_resolver, false, crypt_str("Antiaim.break_resolvers"));

	setup_item(&g_cfg.antiaim.aapresets, 0, crypt_str("Antiaim.aapresets"));
	setup_item(&g_cfg.antiaim.pitch, 0, crypt_str("Antiaim.pitchs"));
	setup_item(&g_cfg.antiaim.base_angle, 0, crypt_str("Antiaim.base_angles"));
	setup_item(&g_cfg.antiaim.yaw, 0, crypt_str("Antiaim.yaws"));
	setup_item(&g_cfg.antiaim.range, 1, crypt_str("Antiaim.ranges"));
	setup_item(&g_cfg.antiaim.speed, 1, crypt_str("Antiaim.speeds"));
	setup_item(&g_cfg.antiaim.desync, 0, crypt_str("Antiaim.desyncs"));
	setup_item(&g_cfg.antiaim.desync_range, 60, crypt_str("Antiaim.desync_ranges"));
	setup_item(&g_cfg.antiaim.inverted_desync_range, 60, crypt_str("Antiaim.inverted_desync_ranges"));
	setup_item(&g_cfg.antiaim.body_lean, 0, crypt_str("Antiaim.body_leans"));
	setup_item(&g_cfg.antiaim.inverted_body_lean, 0, crypt_str("Antiaim.inverted_body_leans"));

	setup_item(&g_cfg.player.enable, false, crypt_str("Player.enables"));
	setup_item(&g_cfg.player.arrows_color, Color(255, 255, 255), crypt_str("Player.arrows_colors"));
	setup_item(&g_cfg.player.arrows, false, crypt_str("Player.arrowss"));
	setup_item(&g_cfg.player.distance, 1, crypt_str("Player.arrows_distances"));
	setup_item(&g_cfg.player.size, 1, crypt_str("Player.arrows_sizes"));
	setup_item(&g_cfg.player.show_multi_points, false, crypt_str("Player.show_multi_pointss"));
	setup_item(&g_cfg.player.show_multi_points_color, Color(255, 255, 255), crypt_str("Player.show_multi_points_colors"));
	setup_item(&g_cfg.player.lag_hitbox, false, crypt_str("Player.lag_hitboxs"));
	setup_item(&g_cfg.player.lag_hitbox_color, Color(255, 255, 255), crypt_str("Player.lag_hitbox_colors"));
	setup_item(&g_cfg.player.player_model_t, 0, crypt_str("Esp.player_model_ts"));
	setup_item(&g_cfg.player.player_model_ct, 0, crypt_str("Esp.player_model_cts"));
	setup_item(&g_cfg.player.local_chams_type, 0, crypt_str("Player.local_chams_types"));
	setup_item(&g_cfg.player.fake_chams_enable, false, crypt_str("Player.fake_chams_enables"));
	setup_item(&g_cfg.player.visualize_lag, false, crypt_str("Player.vizualize_lags"));
	setup_item(&g_cfg.player.layered, false, crypt_str("Player.layereds"));
	setup_item(&g_cfg.player.fake_chams_color, Color(255, 255, 255), crypt_str("Player.fake_chams_colors"));
	setup_item(&g_cfg.player.fake_chams_type, 0, crypt_str("Player.fake_chams_types"));
	setup_item(&g_cfg.player.fake_double_material, false, crypt_str("Player.fake_double_materiala"));
	setup_item(&g_cfg.player.fake_double_material_color, Color(255, 255, 255), crypt_str("Player.fake_double_material_colora"));
	setup_item(&g_cfg.player.fake_animated_material, false, crypt_str("Player.fake_animated_materiald"));
	setup_item(&g_cfg.player.fake_animated_material_color, Color(255, 255, 255), crypt_str("Player.fake_animated_material_colord"));
	setup_item(&g_cfg.player.backtrack_chams, false, crypt_str("Player.backtrack_chamsw"));
	setup_item(&g_cfg.player.backtrack_chams_material, 0, crypt_str("Player.backtrack_chams_materiale"));
	setup_item(&g_cfg.player.backtrack_chams_color, Color(255, 255, 255), crypt_str("Player.backtrack_chams_colors"));
	setup_item(&g_cfg.onshot.chams_on_shot_enable, false, crypt_str("Onshot.onshot_chamsa"));
	setup_item(&g_cfg.onshot.chams_on_shot_color, Color(255, 255, 255), crypt_str("Onshot.onshot_chams_colors"));
	setup_item(&g_cfg.onshot.chams_on_shot_type, 0, crypt_str("Onshot.onshot_chams_types"));
	setup_item(&g_cfg.player.transparency_in_scope, false, crypt_str("Player.transparency_in_scopes"));
	setup_item(&g_cfg.player.transparency_in_scope_amount, 1.0f, crypt_str("Player.transparency_in_scope_amounts"));

	for (auto i = 0; i < 3; i++)
	{
		setup_item(&g_cfg.player.type[i].box, false, std::to_string(i) + crypt_str("Player.boxs"));
		setup_item(&g_cfg.player.type[i].box_color, Color(255, 255, 255), std::to_string(i) + crypt_str("Player.box_colora"));
		setup_item(&g_cfg.player.type[i].name, false, std::to_string(i) + crypt_str("Player.names"));
		setup_item(&g_cfg.player.type[i].name_color, Color(255, 255, 255), std::to_string(i) + crypt_str("Player.name_colord"));
		setup_item(&g_cfg.player.type[i].health, false, std::to_string(i) + crypt_str("Player.healthd"));
		setup_item(&g_cfg.player.type[i].custom_health_color, false, std::to_string(i) + crypt_str("Player.custom_health_colodr"));
		setup_item(&g_cfg.player.type[i].health_color, Color(255, 255, 255), std::to_string(i) + crypt_str("Player.health_coldor"));
		setup_item(&g_cfg.player.type[i].weapon, 2, std::to_string(i) + crypt_str("Player.wesapon"));
		setup_item(&g_cfg.player.type[i].weapon_color, Color(255, 255, 255), std::to_string(i) + crypt_str("Player.weapon_basr_color"));
		setup_item(&g_cfg.player.type[i].skeleton, false, std::to_string(i) + crypt_str("Player.sskeleton"));
		setup_item(&g_cfg.player.type[i].skeleton_color, Color(255, 255, 255), std::to_string(i) + crypt_str("Player.skeletona_color"));
		setup_item(&g_cfg.player.type[i].ammo, false, std::to_string(i) + crypt_str("Player.amsmo"));
		setup_item(&g_cfg.player.type[i].ammobar_color, Color(255, 255, 255), std::to_string(i) + crypt_str("Player.ammobar_colaor"));
		setup_item(&g_cfg.player.type[i].snap_lines, false, std::to_string(i) + crypt_str("Player.snap_laines"));
		setup_item(&g_cfg.player.type[i].snap_lines_color, Color(255, 255, 255), std::to_string(i) + crypt_str("Player.snap_lines_coalor"));
		setup_item(&g_cfg.player.type[i].footsteps, false, std::to_string(i) + crypt_str("Player.footsateps"));
		setup_item(&g_cfg.player.type[i].footsteps_color, Color(255, 255, 255), std::to_string(i) + crypt_str("Player.footsteps_colaor"));
		setup_item(&g_cfg.player.type[i].thickness, 0, std::to_string(i) + crypt_str("Player.thicknaess"));
		setup_item(&g_cfg.player.type[i].radius, 0, std::to_string(i) + crypt_str("Player.raadius"));
		setup_item(&g_cfg.player.type[i].glow, false, std::to_string(i) + crypt_str("Player.gloaw"));
		setup_item(&g_cfg.player.type[i].glow_type, 0, std::to_string(i) + crypt_str("Player.glaow_type"));
		setup_item(&g_cfg.player.type[i].glow_color, Color(255, 255, 255), std::to_string(i) + crypt_str("Player.galow_color"));
		setup_item(&g_cfg.player.type[i].chams, 2, std::to_string(i) + crypt_str("Player.cahams"));
		setup_item(&g_cfg.player.type[i].chams_color, Color(255, 255, 255), std::to_string(i) + crypt_str("Player.chams_color"));
		setup_item(&g_cfg.player.type[i].xqz_color, Color(255, 255, 255), std::to_string(i) + crypt_str("Player.xqz_caolor"));
		setup_item(&g_cfg.player.type[i].chams_type, 0, std::to_string(i) + crypt_str("Player.chamsa_type"));
		setup_item(&g_cfg.player.type[i].double_material, false, std::to_string(i) + crypt_str("Player.doublae_material"));
		setup_item(&g_cfg.player.type[i].double_material_color, Color(255, 255, 255), std::to_string(i) + crypt_str("Player.daouble_material_color"));
		setup_item(&g_cfg.player.type[i].flags, 8, std::to_string(i) + crypt_str("Player.espd_flags"));
	}

	setup_item(&g_cfg.esp.indicators, false, crypt_str("Esp.rage_indicators"));
	setup_item(&g_cfg.esp.removals, 8, crypt_str("Esp.world_removsals"));
	setup_item(&g_cfg.esp.fix_zoom_sensivity, false, crypt_str("Esp.fix_zooms_sensivity"));

	setup_item(&g_cfg.misc.thirdperson_toggle, key_bind(TOGGLE), crypt_str("Misc.thirdperson_toggle"));
	setup_item(&g_cfg.misc.thirdperson_when_spectating, false, crypt_str("Misc.thirdperson_when_spectsating"));
	setup_item(&g_cfg.misc.thirdperson_distance, 100, crypt_str("Misc.thirdperson_distsance"));
	setup_item(&g_cfg.misc.draw_keys, false, crypt_str("Misc.draw_keybindsa"));
	setup_item(&g_cfg.esp.grenade_prediction, false, crypt_str("Esp.grenade_predictiona"));
	setup_item(&g_cfg.esp.on_click, false, crypt_str("Esp.on_clicka"));
	setup_item(&g_cfg.esp.grenade_prediction_color, Color(255, 255, 255), crypt_str("Esp.grenade_prediction_colora"));
	setup_item(&g_cfg.esp.grenade_prediction_tracer_color, Color(255, 255, 255), crypt_str("Esp.grenade_prediction_tracer_coloar"));
	setup_item(&g_cfg.esp.projectiles, false, crypt_str("Esp.projectiales"));
	setup_item(&g_cfg.esp.projectiles_color, Color(255, 255, 255), crypt_str("Esp.projectiles_caolor"));
	setup_item(&g_cfg.esp.bomb_timer, false, crypt_str("Esp.bomb_tiasmer"));
	setup_item(&g_cfg.esp.bright, false, crypt_str("Esp.brighast"));
	setup_item(&g_cfg.esp.nightmode, false, crypt_str("Esp.nightasmode"));
	setup_item(&g_cfg.esp.world_color, Color(255, 255, 255), crypt_str("Esp.world_colsor"));
	setup_item(&g_cfg.esp.props_color, Color(255, 255, 255), crypt_str("Esp.props_colsor"));
	setup_item(&g_cfg.esp.skybox, 0, crypt_str("Esp.skysbox"));
	setup_item(&g_cfg.esp.custom_skybox, crypt_str(""), crypt_str("Esp.custom_skyasbox"));
	setup_item(&g_cfg.esp.skybox_color, Color(255, 255, 255), crypt_str("Esp.skybox_coaslor"));
	setup_item(&g_cfg.esp.client_bullet_impacts, false, crypt_str("Esp.client_bullet_impaascts"));
	setup_item(&g_cfg.esp.client_bullet_impacts_color, Color(255, 255, 255), crypt_str("Esp.client_bullet_impacts_casolor"));
	setup_item(&g_cfg.esp.server_bullet_impacts, false, crypt_str("Esp.server_bullet_impaascts"));
	setup_item(&g_cfg.esp.server_bullet_impacts_color, Color(255, 255, 255), crypt_str("Esp.server_bullet_impacts_coaslor"));
	setup_item(&g_cfg.esp.bullet_tracer, false, crypt_str("Esp.bullet_trasacer"));
	setup_item(&g_cfg.esp.bullet_tracer_color, Color(255, 255, 255), crypt_str("Esp.bullet_tracer_casolor"));
	setup_item(&g_cfg.esp.enemy_bullet_tracer, false, crypt_str("Esp.enemy_bullet_tracaser"));
	setup_item(&g_cfg.esp.enemy_bullet_tracer_color, Color(255, 255, 255), crypt_str("Esp.enemy_bullet_tracer_coaslor"));
	setup_item(&g_cfg.esp.preserve_killfeed, false, crypt_str("Esp.preserve_killasfeed"));
	setup_item(&g_cfg.esp.hitmarker, 2, crypt_str("Esp.hit_masarker"));
	setup_item(&g_cfg.esp.hitmarkers, 0, crypt_str("Esp.hit_masarkers"));
	setup_item(&g_cfg.esp.hitsound, 0, crypt_str("Esp.hitsouasnd"));
	setup_item(&g_cfg.esp.damage_marker, false, crypt_str("Esp.damageas_marker"));
	setup_item(&g_cfg.esp.kill_effect, false, crypt_str("Esp.kill_efasfect"));
	setup_item(&g_cfg.esp.kill_effect_duration, 3.0f, crypt_str("Esp.kill_effect_duraastion"));
	setup_item(&g_cfg.esp.fov, 0, crypt_str("Esp.foasv"));
	setup_item(&g_cfg.esp.viewmodel_fov, 0, crypt_str("Esp.viewmodel_asfov"));
	setup_item(&g_cfg.esp.viewmodel_x, 0, crypt_str("Esp.viewmosddel_x"));
	setup_item(&g_cfg.esp.viewmodel_y, 0, crypt_str("Esp.viewmoddel_y"));
	setup_item(&g_cfg.esp.viewmodel_z, 0, crypt_str("Esp.viewmfodel_z"));
	setup_item(&g_cfg.esp.viewmodel_roll, 0, crypt_str("Esp.viewmodasel_roll"));
	setup_item(&g_cfg.esp.arms_chams, false, crypt_str("Esp.arms_chaams"));
	setup_item(&g_cfg.esp.arms_chams_type, 0, crypt_str("Esp.arms_chasams_type"));
	setup_item(&g_cfg.esp.arms_chams_color, Color(255, 255, 255), crypt_str("Esp.ardms_chams_color"));
	setup_item(&g_cfg.esp.arms_double_material, false, crypt_str("Esp.arms_double_mdaterial"));
	setup_item(&g_cfg.esp.arms_double_material_color, Color(255, 255, 255), crypt_str("Esp.arms_double_material_color"));
	setup_item(&g_cfg.esp.weapon_chams, false, crypt_str("Esp.weapon_chams"));
	setup_item(&g_cfg.esp.weapon_chams_type, 0, crypt_str("Esp.weapon_chams_type"));
	setup_item(&g_cfg.esp.weapon_chams_color, Color(255, 255, 255), crypt_str("Esp.weapon_chams_color"));
	setup_item(&g_cfg.esp.weapon_double_material, false, crypt_str("Esp.weapon_double_material"));
	setup_item(&g_cfg.esp.weapon_double_material_color, Color(255, 255, 255), crypt_str("Esp.weapon_double_material_color"));
	setup_item(&g_cfg.esp.taser_range, false, crypt_str("Esp.taser_rasnge"));
	setup_item(&g_cfg.esp.show_spread, false, crypt_str("Esp.show_spresad"));
	setup_item(&g_cfg.esp.show_spread_color, Color(255, 255, 255), crypt_str("Esp.show_spread_csolor"));
	setup_item(&g_cfg.esp.penetration_reticle, false, crypt_str("Esp.penetration_retsicle"));
	setup_item(&g_cfg.esp.world_modulation, false, crypt_str("Esp.world_modulsation"));
	setup_item(&g_cfg.esp.weapon, 6, crypt_str("Esp.dropped_weapon"));
	setup_item(&g_cfg.esp.box_color, Color(255, 255, 255), crypt_str("Esp.dropped_weapon_bosx_color"));
	setup_item(&g_cfg.esp.weapon_color, Color(255, 255, 255), crypt_str("Esp.dropped_weapon_colsor"));
	setup_item(&g_cfg.esp.weapon_glow_color, Color(255, 255, 255), crypt_str("Esp.dropped_weapons_glow_color"));
	setup_item(&g_cfg.esp.weapon_ammo_color, Color(255, 255, 255), crypt_str("Esp.dropped_weapons_ammo_color"));
	setup_item(&g_cfg.esp.grenade_esp, 4, crypt_str("Esp.grenade_esp"));
	setup_item(&g_cfg.esp.grenade_trail, false, crypt_str("Esp.grenade_trail"));
	setup_item(&g_cfg.esp.grenade_glow_color, Color(255, 255, 255), crypt_str("Esp.grenadse_glow_color"));

	setup_item(&g_cfg.misc.spectators_list, false, crypt_str("Misc.spectators_list"));
	setup_item(&g_cfg.misc.spec_x, 0, crypt_str("Misc.spec_x"));
	setup_item(&g_cfg.misc.spec_y, 0, crypt_str("Misc.spec_y"));
	setup_item(&g_cfg.misc.key_x, 0, crypt_str("Misc.key_x"));
	setup_item(&g_cfg.misc.key_y, 0, crypt_str("Misc.key_y"));
	setup_item(&g_cfg.misc.ingame_radar, false, crypt_str("Misc.ingamase_radar"));
	setup_item(&g_cfg.misc.ragdolls, false, crypt_str("Misc.ragdasolls"));
	setup_item(&g_cfg.misc.bunnyhop, false, crypt_str("Misc.autasohop"));
	setup_item(&g_cfg.misc.airstrafe, 0, crypt_str("Misc.airstrasafe"));
	setup_item(&g_cfg.misc.crouch_in_air, false, crypt_str("Misc.crouasch_in_air"));
	setup_item(&g_cfg.misc.automatic_peek, key_bind(HOLD), crypt_str("Misc.autoasmatic_peek"));
	setup_item(&g_cfg.misc.edge_jump, key_bind(HOLD), crypt_str("Misc.edasge_jump"));
	setup_item(&g_cfg.misc.edgebug, key_bind(HOLD), crypt_str("Misc.edgasebug"));
	setup_item(&g_cfg.misc.jumpbug, key_bind(HOLD), crypt_str("Misc.juasmpbug"));

	setup_item(&g_cfg.misc.noduck, false, crypt_str("Misc.nodasuck"));
	setup_item(&g_cfg.misc.fakeduck_key, key_bind(HOLD), crypt_str("Misc.fakedasuck_key"));
	setup_item(&g_cfg.misc.fast_stop, false, crypt_str("Misc.fast_sastop"));
	setup_item(&g_cfg.misc.slidewalk, false, crypt_str("Misc.slidewasalk"));
	setup_item(&g_cfg.misc.slowwalk_key, key_bind(HOLD), crypt_str("Misc.sloaswwalk_key"));
	setup_item(&g_cfg.misc.chat, false, crypt_str("Misc.chasat"));
	setup_item(&g_cfg.misc.log_output, 2, crypt_str("Misc.loasg_output"));
	setup_item(&g_cfg.misc.events_to_log, 3, crypt_str("Misc.eveasnts_to_log"));
	setup_item(&g_cfg.misc.background, 0, crypt_str("Misc.background"));
	setup_item(&g_cfg.misc.force_background, false, crypt_str("Misc.force_background"));
	setup_item(&g_cfg.misc.show_default_log, false, crypt_str("Misc.shoasw_default_log"));
	setup_item(&g_cfg.misc.log_color, Color(255, 255, 255), crypt_str("Misc.loasg_color"));
	setup_item(&g_cfg.misc.inventory_access, false, crypt_str("Misc.inventasory_access"));
	setup_item(&g_cfg.misc.rank_reveal, false, crypt_str("Misc.rank_reasveal"));
	setup_item(&g_cfg.misc.clantag_spammer, false, crypt_str("Misc.clanastag_spammer"));
	setup_item(&g_cfg.misc.aspect_ratio, false, crypt_str("Misc.aspect_ratasio"));
	setup_item(&g_cfg.misc.aspect_ratio_amount, 1.0f, crypt_str("Misc.aspecast_ratio_amount"));
	setup_item(&g_cfg.misc.anti_screenshot, false, crypt_str("Misc.anti_scraseenshot"));
	setup_item(&g_cfg.misc.anti_untrusted, true, crypt_str("Misc.antiuntrusasted"));
	setup_item(&g_cfg.misc.buybot_enable, false, crypt_str("Misc.buyasbot"));
	setup_item(&g_cfg.misc.buybot1, 0, crypt_str("Player.buybasot1"));
	setup_item(&g_cfg.misc.buybot2, 0, crypt_str("Player.buyasbot2"));
	setup_item(&g_cfg.misc.buybot3, 4, crypt_str("Misc.buyboast3"));

	setup_item(&g_cfg.menu.menu_theme, Color(255, 255, 255), crypt_str("Menu.menasu_color"));
	setup_item(&g_cfg.menu.watermark, true, crypt_str("Menu.watermark"));

}

void C_ConfigManager::add_item(void* pointer, const char* name, const std::string& type) {
	items.push_back(new C_ConfigItem(std::string(name), pointer, type));
}

void C_ConfigManager::setup_item(int* pointer, int value, const std::string& name)
{
	add_item(pointer, name.c_str(), crypt_str("int"));
	*pointer = value;
}

void C_ConfigManager::setup_item(bool* pointer, bool value, const std::string& name)
{
	add_item(pointer, name.c_str(), crypt_str("bool"));
	*pointer = value;
}

void C_ConfigManager::setup_item(float* pointer, float value, const std::string& name)
{
	add_item(pointer, name.c_str(), crypt_str("float"));
	*pointer = value;
}

void C_ConfigManager::setup_item(key_bind* pointer, key_bind value, const std::string& name) //-V813
{
	add_item(pointer, name.c_str(), crypt_str("KeyBind"));
	*pointer = value;
}

void C_ConfigManager::setup_item(Color* pointer, Color value, const std::string& name)
{
	colors[name][0] = (float)value.r() / 255.0f;
	colors[name][1] = (float)value.g() / 255.0f;
	colors[name][2] = (float)value.b() / 255.0f;
	colors[name][3] = (float)value.a() / 255.0f;

	add_item(pointer, name.c_str(), crypt_str("Color"));
	*pointer = value;
}

void C_ConfigManager::setup_item(std::vector< int >* pointer, int size, const std::string& name)
{
	add_item(pointer, name.c_str(), crypt_str("vector<int>"));
	pointer->clear();

	for (int i = 0; i < size; i++)
		pointer->push_back(FALSE);
}

void C_ConfigManager::setup_item(std::vector< std::string >* pointer, const std::string& name)
{
	add_item(pointer, name.c_str(), crypt_str("vector<string>"));
}

void C_ConfigManager::setup_item(std::string* pointer, const std::string& value, const std::string& name)
{
	add_item(pointer, name.c_str(), crypt_str("string"));
	*pointer = value; //-V820
}

void C_ConfigManager::save(std::string config)
{
	std::string folder, file;

	auto get_dir = [&folder, &file, &config]() -> void
	{
		static TCHAR path[MAX_PATH];

		if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, NULL, path)))
		{
			folder = std::string(path) + crypt_str("\\Snazzy\\Configs\\");
			file = std::string(path) + crypt_str("\\Snazzy\\Configs\\") + config;
		}

		CreateDirectory(folder.c_str(), NULL);
	};

	get_dir();
	json allJson;

	for (auto it : items)
	{
		json j;

		j[crypt_str("name")] = it->name;
		j[crypt_str("type")] = it->type;

		if (!it->type.compare(crypt_str("int")))
			j[crypt_str("value")] = (int)*(int*)it->pointer; //-V206
		else if (!it->type.compare(crypt_str("float")))
			j[crypt_str("value")] = (float)*(float*)it->pointer;
		else if (!it->type.compare(crypt_str("bool")))
			j[crypt_str("value")] = (bool)*(bool*)it->pointer;
		else if (!it->type.compare(crypt_str("KeyBind")))
		{
			auto k = *(key_bind*)(it->pointer);

			std::vector <int> a = { k.key, k.mode };
			json ja;

			for (auto& i : a)
				ja.push_back(i);

			j[crypt_str("value")] = ja.dump();
		}
		else if (!it->type.compare(crypt_str("Color")))
		{
			auto c = *(Color*)(it->pointer);

			std::vector<int> a = { c.r(), c.g(), c.b(), c.a() };
			json ja;

			for (auto& i : a)
				ja.push_back(i);

			j[crypt_str("value")] = ja.dump();
		}
		else if (!it->type.compare(crypt_str("vector<int>")))
		{
			auto& ptr = *(std::vector<int>*)(it->pointer);
			json ja;

			for (auto& i : ptr)
				ja.push_back(i);

			j[crypt_str("value")] = ja.dump();
		}
		else if (!it->type.compare(crypt_str("vector<string>")))
		{
			auto& ptr = *(std::vector<std::string>*)(it->pointer);
			json ja;

			for (auto& i : ptr)
				ja.push_back(i);

			j[crypt_str("value")] = ja.dump();
		}
		else if (!it->type.compare(crypt_str("string")))
			j[crypt_str("value")] = (std::string) * (std::string*)it->pointer;

		allJson.push_back(j);
	}

	auto get_type = [](menu_item_type type)
	{
		switch (type) //-V719
		{
		case CHECK_BOX:
			return "bool";
		case COMBO_BOX:
		case SLIDER_INT:
			return "int";
		case SLIDER_FLOAT:
			return "float";
		case COLOR_PICKER:
			return "Color";
		}
	};

	std::string data;

	Base64 base64;
	base64.encode(allJson.dump(), &data);

	std::ofstream ofs;
	ofs.open(file + '\0', std::ios::out | std::ios::trunc);

	ofs << std::setw(4) << data << std::endl;
	ofs.close();
}

void C_ConfigManager::load(std::string config, bool load_script_items)
{
	static auto find_item = [](std::vector< C_ConfigItem* > items, std::string name) -> C_ConfigItem*
	{
		for (int i = 0; i < (int)items.size(); i++) //-V202
			if (!items[i]->name.compare(name))
				return items[i];

		return nullptr;
	};

	std::string folder, file;

	auto get_dir = [&folder, &file, &config]() ->void
	{
		static TCHAR path[MAX_PATH];

		if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, NULL, path)))
		{
			folder = std::string(path) + crypt_str("\\Snazzy\\Configs\\");
			file = std::string(path) + crypt_str("\\Snazzy\\Configs\\") + config;
		}

		CreateDirectory(folder.c_str(), NULL);
	};

	get_dir();
	std::string data;

	std::ifstream ifs;
	ifs.open(file + '\0');

	ifs >> data;
	ifs.close();

	if (data.empty())
		return;

	Base64 base64;

	std::string decoded_data;
	base64.decode(data, &decoded_data);

	std::ofstream ofs;
	ofs.open(file + '\0', std::ios::out | std::ios::trunc);

	ofs << decoded_data;
	ofs.close();

	json allJson;

	std::ifstream ifs_final;
	ifs_final.open(file + '\0');

	ifs_final >> allJson;
	ifs_final.close();

	base64.encode(allJson.dump(), &data);

	std::ofstream final_ofs;
	final_ofs.open(file + '\0', std::ios::out | std::ios::trunc);

	final_ofs << data;
	final_ofs.close();

	for (auto it = allJson.begin(); it != allJson.end(); ++it)
	{
		json j = *it;

		std::string name = j[crypt_str("name")];
		std::string type = j[crypt_str("type")];

		if (!load_script_items)
		{
			auto item = find_item(items, name);

			if (item)
			{
				if (!type.compare(crypt_str("int")))
					*(int*)item->pointer = j[crypt_str("value")].get<int>(); //-V206
				else if (!type.compare(crypt_str("float")))
					*(float*)item->pointer = j[crypt_str("value")].get<float>();
				else if (!type.compare(crypt_str("bool")))
					*(bool*)item->pointer = j[crypt_str("value")].get<bool>();
				else if (!type.compare(crypt_str("KeyBind")))
				{
					std::vector<int> a;
					json ja = json::parse(j[crypt_str("value")].get<std::string>().c_str());

					for (json::iterator it = ja.begin(); it != ja.end(); ++it)
						a.push_back(*it);

					*(key_bind*)item->pointer = key_bind((ButtonCode_t)a[0], (key_bind_mode)a[1]);
				}
				else if (!type.compare(crypt_str("Color")))
				{
					std::vector<int> a;
					json ja = json::parse(j[crypt_str("value")].get<std::string>().c_str());

					for (json::iterator it = ja.begin(); it != ja.end(); ++it)
						a.push_back(*it);

					colors.erase(item->name);
					*(Color*)item->pointer = Color(a[0], a[1], a[2], a[3]);
				}
				else if (!type.compare(crypt_str("vector<int>")))
				{
					auto ptr = static_cast<std::vector <int>*> (item->pointer);
					ptr->clear();

					json ja = json::parse(j[crypt_str("value")].get<std::string>().c_str());

					for (json::iterator it = ja.begin(); it != ja.end(); ++it)
						ptr->push_back(*it);
				}
				else if (!type.compare(crypt_str("vector<string>")))
				{
					auto ptr = static_cast<std::vector <std::string>*> (item->pointer);
					ptr->clear();

					json ja = json::parse(j[crypt_str("value")].get<std::string>().c_str());

					for (json::iterator it = ja.begin(); it != ja.end(); ++it)
						ptr->push_back(*it);
				}
				else if (!type.compare(crypt_str("string")))
					*(std::string*)item->pointer = j[crypt_str("value")].get<std::string>();
			}
		}
	}
}

void C_ConfigManager::remove(std::string config)
{
	std::string folder, file;

	auto get_dir = [&folder, &file, &config]() -> void
	{
		static TCHAR path[MAX_PATH];

		if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, NULL, path)))
		{
			folder = std::string(path) + crypt_str("\\Snazzy\\Configs\\");
			file = std::string(path) + crypt_str("\\Snazzy\\Configs\\") + config;
		}

		CreateDirectory(folder.c_str(), NULL);
	};

	get_dir();

	std::string path = file + '\0';
	std::remove(path.c_str());
}

void C_ConfigManager::config_files()
{
	std::string folder;

	auto get_dir = [&folder]() -> void
	{
		static TCHAR path[MAX_PATH];

		if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, NULL, path)))
			folder = std::string(path) + crypt_str("\\Snazzy\\Configs\\");

		CreateDirectory(folder.c_str(), NULL);
	};

	get_dir();
	files.clear();

	std::string path = folder + crypt_str("/*");
	WIN32_FIND_DATA fd;

	HANDLE hFind = FindFirstFile(path.c_str(), &fd);

	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
				files.push_back(fd.cFileName);
		} while (FindNextFile(hFind, &fd));

		FindClose(hFind);
	}
}
