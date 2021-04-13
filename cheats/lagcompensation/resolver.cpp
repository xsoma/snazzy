#include "animation_system.h"
#include "../ragebot/aim.h"
#include "../../utils/math.hpp"
#include "../misc/logs.h"

/// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                              /// --INITIALIZE RESOLVER-- ///                                                                  
/// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int last_ticks[65];
int player_t::GetChokedPackets() {
	auto ticks = TIME_TO_TICKS(m_flSimulationTime() - m_flOldSimulationTime());
	if (ticks == 0 && last_ticks[EntIndex()] > 0) {
		return last_ticks[EntIndex()] - 1;
	}
	else {
		last_ticks[EntIndex()] = ticks;
		return ticks;
	}
}

float AngleMod(float a)
{
	return (360.f / 65536) * ((int)(a * (65536.f / 360.0f)) & 65535);
}

float ApproachAngle(float target, float value, float speed)
{
	target = AngleMod(target);
	value = AngleMod(value);

	float delta = target - value;

	// Speed is assumed to be positive
	if (speed < 0)
		speed = -speed;

	if (delta < -180)
		delta += 360;
	else if (delta > 180)
		delta -= 360;

	if (delta > speed)
		value += speed;
	else if (delta < -speed)
		value -= speed;
	else
		value = target;

	return value;
}

float get_backward_side(player_t* player)
{
	return math::calculate_angle(g_ctx.local()->m_vecOrigin(), player->m_vecOrigin()).y;
}

void resolver::initialize(player_t* e, adjust_data* record, const float& goal_feet_yaw, const float& pitch)
{
	player = e;
	player_record = record;

	original_goal_feet_yaw = math::normalize_yaw(goal_feet_yaw);
	original_pitch = math::normalize_pitch(pitch);
}

/// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                              /// --RESET RESOLVER-- ///                                                                  
/// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void resolver::reset()
{
	player = nullptr;
	player_record = nullptr;

	side = false;
	fake = false;

	was_first_bruteforce = false;
	was_second_bruteforce = false;

	original_goal_feet_yaw = 0.0f;
	original_pitch = 0.0f;
}

void resolver::resolve(player_t* e)
{
	/// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///                                                              /// --LEGIT CHECK-- ///                                                                  
	/// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	auto animstate = e->get_animation_state();

	if (e->GetChokedPackets() <= 0)
		return;

	if (!animstate)
		return;

	animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y);

	if (!(g_ctx.local()->is_alive()))
		return;

	/// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///                                                              /// --PREPARATIONS-- ///                                                                  
	/// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	auto entity_index = e->EntIndex();

	auto entity_index2 = e->EntIndex() - 1;


	AnimationLayer* pLayer = e->get_animlayers();
	AnimationLayer server_animlayers[15];
	AnimationLayer resolver_animlayers[3][15];
	AnimationLayer previous_animlayers[15];
	memcpy(server_animlayers, resolver_animlayers, sizeof(AnimationLayer) * 15);


	/// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///                                                              /// --CHECKS-- ///                                                                  
	/// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	const auto slowwalk = animstate->m_flFeetYawRate >= 0.01f && animstate->m_flFeetYawRate <= 0.8f && e->m_vecVelocity().Length2D() <= 110.f && e->m_fFlags() & FL_ONGROUND;

	auto moving = e->m_vecVelocity().Length2D() > 175.f && e->m_fFlags() & FL_ONGROUND;

	const auto jumping = !(e->m_fFlags() & FL_ONGROUND);

	auto active_weapon = e->m_hActiveWeapon()->m_iItemDefinitionIndex();

	if (!(e->m_bIsScoped()) && active_weapon == WEAPON_SCAR20 || active_weapon == WEAPON_G3SG1)
	{
		moving = e->m_vecVelocity().Length2D() >= 200.f && e->m_vecVelocity().Length2D() <= 220.f && e->m_fFlags() & FL_ONGROUND;
	}
	else if (e->m_bIsScoped() && active_weapon == WEAPON_SCAR20 || active_weapon == WEAPON_G3SG1)
	{
		moving = e->m_vecVelocity().Length2D() >= 100.f && e->m_vecVelocity().Length2D() <= 120.f && e->m_fFlags() & FL_ONGROUND;
	}
	else if (active_weapon == WEAPON_SSG08)
	{
		moving = e->m_vecVelocity().Length2D() >= 210.f && e->m_vecVelocity().Length2D() <= 230.f && e->m_fFlags() & FL_ONGROUND;
	}
	else if (!(e->m_bIsScoped()) && active_weapon == WEAPON_AWP)
	{
		moving = e->m_vecVelocity().Length2D() >= 180.f && e->m_vecVelocity().Length2D() <= 200.f && e->m_fFlags() & FL_ONGROUND;
	}
	else if (e->m_bIsScoped() && active_weapon == WEAPON_AWP)
	{
		moving = e->m_vecVelocity().Length2D() >= 80.f && e->m_vecVelocity().Length2D() <= 100.f && e->m_fFlags() & FL_ONGROUND;
	}
	else if (active_weapon == WEAPON_DEAGLE)
	{
		moving = e->m_vecVelocity().Length2D() >= 210.f && e->m_vecVelocity().Length2D() <= 230.f && e->m_fFlags() & FL_ONGROUND;
	}
	else if (active_weapon == WEAPON_REVOLVER)
	{
		moving = e->m_vecVelocity().Length2D() >= 170.f && e->m_vecVelocity().Length2D() <= 190.f && e->m_fFlags() & FL_ONGROUND;
	}
	else if (active_weapon == WEAPONTYPE_PISTOL)
	{
		moving = e->m_vecVelocity().Length2D() >= 220.f && e->m_vecVelocity().Length2D() <= 240.f && e->m_fFlags() & FL_ONGROUND;
	}
	else if (active_weapon == WEAPONTYPE_KNIFE || active_weapon == WEAPONTYPE_C4)
	{
		moving = e->m_vecVelocity().Length2D() >= 230.f && e->m_vecVelocity().Length2D() <= 250.f && e->m_fFlags() & FL_ONGROUND;
	}
	else if (active_weapon == WEAPON_TASER)
	{
		moving = e->m_vecVelocity().Length2D() >= 200.f && e->m_vecVelocity().Length2D() <= 220.f && e->m_fFlags() & FL_ONGROUND;
	}
	else if (active_weapon == WEAPONTYPE_GRENADE)
	{
		moving = e->m_vecVelocity().Length2D() >= 230.f && e->m_vecVelocity().Length2D() <= 250.f && e->m_fFlags() & FL_ONGROUND;
	}
	else if (active_weapon == WEAPONTYPE_RIFLE)
	{
		moving = e->m_vecVelocity().Length2D() >= 200.f && e->m_vecVelocity().Length2D() <= 220.f && e->m_fFlags() & FL_ONGROUND;
	}
	else if (active_weapon == WEAPONTYPE_SUBMACHINEGUN)
	{
		moving = e->m_vecVelocity().Length2D() >= 200.f && e->m_vecVelocity().Length2D() <= 240.f && e->m_fFlags() & FL_ONGROUND;
	}
	else if (active_weapon == WEAPONTYPE_SUBMACHINEGUN)
	{
		moving = e->m_vecVelocity().Length2D() >= 200.f && e->m_vecVelocity().Length2D() <= 240.f && e->m_fFlags() & FL_ONGROUND;
	}
	else if (active_weapon == WEAPON_NEGEV)
	{
		moving = e->m_vecVelocity().Length2D() >= 130.f && e->m_vecVelocity().Length2D() <= 150.f && e->m_fFlags() & FL_ONGROUND;
	}
	else if (active_weapon == WEAPON_M249)
	{
		moving = e->m_vecVelocity().Length2D() >= 175.f && e->m_vecVelocity().Length2D() <= 195.f && e->m_fFlags() & FL_ONGROUND;
	}
	else if (active_weapon == WEAPONTYPE_SHOTGUN)
	{
		moving = e->m_vecVelocity().Length2D() >= 195.f && e->m_vecVelocity().Length2D() <= 225.f && e->m_fFlags() & FL_ONGROUND;
	}


	//const auto legitaa = animstate->m_flPitch < 20 && animstate->m_flPitch > -20 && e->GetChokedPackets() > 0;

	/// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///                                                              /// --LOGIC-- ///                                                                  
	/// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	auto velocity = e->m_vecVelocity(); //velocity

	auto weapon = e->m_hActiveWeapon(); //active weapon

	float cycle = (pLayer->m_flPlaybackRate * animstate->m_flLastClientSideAnimationUpdateTime) + pLayer->m_flCycle;

	cycle -= (float)(int)cycle;

	if (cycle < 0.0f)
		cycle += 1.0f;

	if (cycle > 1.0f)
		cycle -= 1.0f;


	float max_speed = 260.0f;

	if (weapon)
		max_speed = std::fmax(weapon->get_csweapon_info()->flMaxPlayerSpeed, 0.001f);

	auto unknown_velocity = *(float*)(uintptr_t(animstate) + 0x2A4);

	if (animstate->m_flFeetSpeedUnknownForwardOrSideways < 1.0f)
	{
		if (animstate->m_flFeetSpeedUnknownForwardOrSideways < 0.5f)
		{
			float velocity = unknown_velocity;
			float delta = animstate->m_flLastClientSideAnimationUpdateTime * 60.0f;
			float new_velocity;
			if ((80.0f - velocity) <= delta)
			{
				if (-delta <= (80.0f - velocity))
					new_velocity = 80.0f;
				else
					new_velocity = velocity - delta;
			}
			else
			{
				new_velocity = velocity + delta;
			}
			unknown_velocity = new_velocity;
		}
	}

	bool WasMovingLastUpdate = false;
	bool JustStartedMovingLastUpdate = false;

	if (e->m_vecVelocity().Length2D() <= 0.0f)
	{
		animstate->m_flTimeSinceStartedMoving = 0.0f;
		WasMovingLastUpdate = animstate->m_flTimeSinceStoppedMoving <= 0.0f;
		animstate->m_flTimeSinceStoppedMoving += animstate->m_flLastClientSideAnimationUpdateTime;
	}
	else
	{
		animstate->m_flTimeSinceStoppedMoving = 0.0f;
		JustStartedMovingLastUpdate = animstate->m_flTimeSinceStartedMoving <= 0.0f;
		animstate->m_flTimeSinceStartedMoving = animstate->m_flLastClientSideAnimationUpdateTime + animstate->m_flTimeSinceStartedMoving;
	}

	animstate->m_flCurrentFeetYaw = animstate->AbsYaw();

	auto v47 = std::clamp(animstate->AbsYaw(), -360.0f, 360.0f);
	auto v49 = math::normalize_yaw(math::angle_diff(animstate->m_flEyeYaw, v47));

	if (animstate->m_flFeetSpeedForwardsOrSideWays >= 0.0)
		animstate->m_flFeetSpeedForwardsOrSideWays = fminf(animstate->m_flFeetSpeedForwardsOrSideWays, 1.0);
	else
		animstate->m_flFeetSpeedForwardsOrSideWays = 0.0;

	auto v54 = animstate->m_fDuckAmount;
	auto v55 = ((((*(float*)((uintptr_t)animstate + 0x11C)) * -0.30000001) - 0.19999999) * animstate->m_flFeetSpeedForwardsOrSideWays) + 1.0f;
	if (v54 > 0.0)
	{
		if (animstate->m_flFeetSpeedUnknownForwardOrSideways >= 0.0)
			animstate->m_flFeetSpeedUnknownForwardOrSideways = fminf(animstate->m_flFeetSpeedUnknownForwardOrSideways, 1.0);
		else
			animstate->m_flFeetSpeedUnknownForwardOrSideways = 0.0;

		v55 += ((animstate->m_flFeetSpeedUnknownForwardOrSideways * v54) * (0.5f - v55));
	}

	auto v58 = *(float*)((uintptr_t)animstate + 0x334) * v55;
	auto v59 = *(float*)((uintptr_t)animstate + 0x330) * v55;

	if (v49 <= v58)
	{
		if (v59 > v49)
			animstate->m_flGoalFeetYaw = fabs(v59) + animstate->m_flEyeYaw;
	}
	else
		animstate->m_flGoalFeetYaw = animstate->m_flEyeYaw - fabs(v58);

	animstate->m_flGoalFeetYaw = math::normalize_yaw(animstate->m_flGoalFeetYaw);

	if (e->m_vecVelocity().Length2D() > 0.1 || fabs(animstate->flUpVelocity) > 100.0)
	{
		animstate->m_flGoalFeetYaw = ApproachAngle(
			animstate->m_flEyeYaw,
			animstate->AbsYaw(),
			(((*(float*)((uintptr_t)animstate + 0x11C)) * 20.0f) + 30.0f)
			* animstate->m_flLastClientSideAnimationUpdateTime);
	}
	else
	{
		animstate->m_flGoalFeetYaw = ApproachAngle(
			e->m_flLowerBodyYawTarget(),
			animstate->AbsYaw(),
			animstate->m_flLastClientSideAnimationUpdateTime * 100.0f);

	}


	bool balance_adjust[128];

	if (e->m_vecVelocity().Length2D() <= 1.0
		&& animstate->m_bOnGround
		&& animstate->m_flLastClientSideAnimationUpdateTime > 0.0
		&& (math::angle_diff(animstate->m_flCurrentFeetYaw, animstate->AbsYaw()) / animstate->m_flLastClientSideAnimationUpdateTime) > 120.0)
	{
		balance_adjust[entity_index2] = true;
	}
	else
		balance_adjust[entity_index2] = false;

	if (e->m_vecVelocity().Length2D() > 0.0)
	{
		float velAngle = (atan2(-e->m_vecVelocity().y, -e->m_vecVelocity().x) * 180.0f) * (1.0f / M_PI);

		if (velAngle < 0.0f)
			velAngle += 360.0f;

		animstate->m_flUnknownVelocityLean = math::normalize_yaw(math::angle_diff(velAngle, animstate->AbsYaw()));
	}

	animstate->m_flLeanAmount = math::normalize_yaw(math::angle_diff(animstate->m_flUnknownVelocityLean, animstate->m_flCurrentTorsoYaw));

	if (JustStartedMovingLastUpdate && animstate->m_flFeetYawRate <= 0.0)
	{
		animstate->m_flCurrentTorsoYaw = animstate->m_flUnknownVelocityLean;
	}
	else
	{
		if (e->m_vecVelocity().Length2D() > 0.1f)
		{
			animstate->m_flCurrentTorsoYaw = animstate->m_flUnknownVelocityLean;
		}
		else
		{
			if (animstate->m_flFeetSpeedUnknownForwardOrSideways >= 0.0)
				animstate->m_flFeetSpeedUnknownForwardOrSideways = fminf(animstate->m_flFeetSpeedUnknownForwardOrSideways, 1.0);
			else
				animstate->m_flFeetSpeedUnknownForwardOrSideways = 0.0;

			if (animstate->m_flFeetSpeedForwardsOrSideWays >= 0.0)
				animstate->m_flFeetSpeedForwardsOrSideWays = fminf(animstate->m_flFeetSpeedForwardsOrSideWays, 1.0);
			else
				animstate->m_flFeetSpeedForwardsOrSideWays = 0.0;



			auto v105 = ((animstate->m_flFeetSpeedUnknownForwardOrSideways - animstate->m_flFeetSpeedForwardsOrSideWays) * animstate->m_fDuckAmount) + animstate->m_flFeetSpeedForwardsOrSideWays;
			auto v156 = math::normalize_yaw((((v105 + 0.1f) * animstate->m_flUnknownVelocityLean) + animstate->m_flCurrentTorsoYaw));

			animstate->m_flCurrentTorsoYaw = v156;
		}
	}

	/// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///                                                              /// --SIDE DETECTION-- ///                                                                  
	/// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	float eyegoalfeetdelta = math::angle_diff(animstate->m_flEyeYaw - animstate->m_flGoalFeetYaw, 360.0f);

	float new_body_yaw = 0.0f;



	if (e->m_vecVelocity().Length2D() <= 0.1)
	{
		if (server_animlayers[ANIMATION_LAYER_ADJUST].m_flWeight == 0.0
			&& server_animlayers[ANIMATION_LAYER_ADJUST].m_flCycle == 0.0)
		{
			side = 2 * (math::angle_diff(animstate->m_flEyeYaw, animstate->m_flGoalFeetYaw) <= 0.0) - 1;
		}
	}
	else if (!(server_animlayers[ANIMATION_LAYER_LEAN].m_flWeight * 1000.0) && (server_animlayers[ANIMATION_LAYER_MOVEMENT_MOVE].m_flWeight * 1000.0) == (previous_animlayers[ANIMATION_LAYER_MOVEMENT_MOVE].m_flWeight * 1000.0)) //the shit was 1000 iirc u can double check if u want
	{
		auto first_delta = abs(server_animlayers[ANIMATION_LAYER_MOVEMENT_MOVE].m_flPlaybackRate - resolver_animlayers[ANIMATION_LAYER_AIMMATRIX][ANIMATION_LAYER_MOVEMENT_MOVE].m_flPlaybackRate);
		auto second_delta = abs(server_animlayers[ANIMATION_LAYER_MOVEMENT_MOVE].m_flPlaybackRate - resolver_animlayers[ANIMATION_LAYER_WEAPON_ACTION_RECROUCH][ANIMATION_LAYER_MOVEMENT_MOVE].m_flPlaybackRate);
		auto third_delta = abs(server_animlayers[ANIMATION_LAYER_MOVEMENT_MOVE].m_flPlaybackRate - resolver_animlayers[ANIMATION_LAYER_WEAPON_ACTION][ANIMATION_LAYER_MOVEMENT_MOVE].m_flPlaybackRate);

		if (first_delta < second_delta || third_delta <= second_delta || (second_delta * 1000.0))
		{
			if (first_delta >= third_delta && second_delta > third_delta && !(third_delta * 1000.0))
			{
				side = 1;
			}
		}
		else
		{
			side = -1;
		}
	}

	if (side == 0)
	{

		/*if (eyegoalfeetdelta < 0.0f || (*(float*)((DWORD)animstate + 0x330)) == 0.0f)
		{
			if ((*(float*)((DWORD)animstate + 0x330)) != 0.0f)
				new_body_yaw = (eyegoalfeetdelta / (*(float*)((DWORD)animstate + 0x330))) * -58.0f;
		}
		else
		{
			new_body_yaw = (eyegoalfeetdelta / (*(float*)((DWORD)animstate + 0x334))) * 58.0f;
		}

		if (new_body_yaw > 10.f)
			side = 1;
		else if (new_body_yaw < -10.f)
			side = -1;
		else
			side = 0;*/

			//if (side == 0)
			//{

				/* externs */
		Vector src3D, dst3D, forward, right, up, src, dst;
		float back_two, right_two, left_two;
		CGameTrace tr;
		CTraceFilter filter;

		/* angle vectors */
		math::angle_vectors(Vector(0, get_backward_side(e), 0), &forward, &right, &up);

		/* filtering */
		filter.SetPassEntity(e);
		src3D = e->get_shoot_position();
		dst3D = src3D + (forward * 384);

		/* back engine tracers */
		m_trace()->TraceRay(Ray_t(src3D, dst3D), MASK_SHOT, &filter, &tr);
		back_two = (tr.endpos - tr.startpos).Length();

		/* right engine tracers */
		m_trace()->TraceRay(Ray_t(src3D + right * 35, dst3D + right * 35), MASK_SHOT, &filter, &tr);
		right_two = (tr.endpos - tr.startpos).Length();

		/* left engine tracers */
		m_trace()->TraceRay(Ray_t(src3D - right * 35, dst3D - right * 35), MASK_SHOT, &filter, &tr);
		left_two = (tr.endpos - tr.startpos).Length();

		/* side detection */
		if (left_two > right_two) {
			side = -1;
		}
		else if (right_two > left_two) {
			side = 1;
		}
		else
			side = 0;
		//}
	}

	if (g_ctx.globals.missed_shots_reset[entity_index] == 1)
	{
		if (side == -1)
			side = 1;
		else if (side == 1)
			side = -1;
	}
	if (g_ctx.globals.missed_shots_reset[entity_index] == 3)
	{
		if (side == -1)
			side = 1;
		else if (side == 1)
			side = -1;
	}
	if (g_ctx.globals.missed_shots_reset[entity_index] == 4)
	{
		if (side == -1)
			side = 1;
		else if (side == 1)
			side = -1;
	}
	if (g_ctx.globals.missed_shots_reset[entity_index] == 6)
	{
		if (side == -1)
			side = 1;
		else if (side == 1)
			side = -1;
	}
	if (g_ctx.globals.missed_shots_reset[entity_index] == 8)
	{
		if (side == -1)
			side = 1;
		else if (side == 1)
			side = -1;
	}
	if (g_ctx.globals.missed_shots_reset[entity_index] == 9)
	{
		if (side == -1)
			side = 1;
		else if (side == 1)
			side = -1;
	}
	if (g_ctx.globals.missed_shots_reset[entity_index] == 11)
	{
		if (side == -1)
			side = 1;
		else if (side == 1)
			side = -1;
	}
	if (g_ctx.globals.missed_shots_reset[entity_index] == 13)
	{
		if (side == -1)
			side = 1;
		else if (side == 1)
			side = -1;
	}
	if (g_ctx.globals.missed_shots_reset[entity_index] == 15)
	{
		if (side == -1)
			side = 1;
		else if (side == 1)
			side = -1;
	}
	if (g_ctx.globals.missed_shots_reset[entity_index] == 17)
	{
		if (side == -1)
			side = 1;
		else if (side == 1)
			side = -1;
	}
	if (g_ctx.globals.missed_shots_reset[entity_index] == 19)
	{
		if (side == -1)
			side = 1;
		else if (side == 1)
			side = -1;
	}
	if (g_ctx.globals.missed_shots_reset[entity_index] == 21)
	{
		if (side == -1)
			side = 1;
		else if (side == 1)
			side = -1;
	}
	if (g_ctx.globals.missed_shots_reset[entity_index] == 23)
	{
		if (side == -1)
			side = 1;
		else if (side == 1)
			side = -1;
	}
	if (g_ctx.globals.missed_shots_reset[entity_index] == 25)
	{
		if (side == -1)
			side = 1;
		else if (side == 1)
			side = -1;
	}


	/// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///                                                              /// --RESOLVE-- ///                                                                  
	/// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*if (legitaa)
	{
		if (moving)
		{
			if (side == 1)
			{
				animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y - 10.f);
			}
			else if (side == -1)
			{
				animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y + 10.f);
			}
			else
			{
				animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y);
			}

			if (g_ctx.globals.missed_shots_reset[entity_index] == 1)
			{
				animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y);
			}
		}
		else if (jumping)
		{
			if (side == 1)
			{
				switch (g_ctx.globals.missed_shots[entity_index] % 4)
				{
				case 0:
					animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y - 13.f);
					break;
				case 1:
					animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y - 33.f);
					break;
				case 2:
					animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y - 53.f);
					break;
				case 3:
					animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y);
					break;
				}
			}
			else if (side == -1)
			{
				switch (g_ctx.globals.missed_shots[entity_index] % 4)
				{
				case 0:
					animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y + 13.f);
					break;
				case 1:
					animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y + 33.f);
					break;
				case 2:
					animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y + 53.f);
					break;
				case 3:
					animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y);
					break;
				}
			}
			else
			{
				animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y);
			}
		}
		else if (slowwalk)
		{
			if (side == 1)
			{
				switch (g_ctx.globals.missed_shots[entity_index] % 3)
				{
				case 0:
					animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y - 38.f);
					break;
				case 1:
					animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y - 58.f);
					break;
				case 2:
					animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y - 18.f);
					break;
				}
			}
			else if (side == -1)
			{
				switch (g_ctx.globals.missed_shots[entity_index] % 3)
				{
				case 0:
					animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y + 38.f);
					break;
				case 1:
					animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y + 58.f);
					break;
				case 2:
					animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y + 18.f);
					break;
				}
			}
			else
			{
				animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y);
			}
		}
		else
		{
			if (side == 1)
			{
				if (e->m_bDucked())
				{
					switch (g_ctx.globals.missed_shots[entity_index] % 3)
					{
					case 0:
						animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y + 58.f);
						break;
					case 1:
						animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y + 38.f);
						break;
					case 2:
						animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y + 18.f);
						break;
					}
				}
				else
				{
					switch (g_ctx.globals.missed_shots[entity_index] % 3)
					{
					case 0:
						animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y + 38.f);
						break;
					case 1:
						animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y + 58.f);
						break;
					case 2:
						animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y + 18.f);
						break;
					}
				}
			}
			else if (side == -1)
			{
				if (e->m_bDucked())
				{
					switch (g_ctx.globals.missed_shots[entity_index] % 3)
					{
					case 0:
						animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y - 58.f);
						break;
					case 1:
						animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y - 38.f);
						break;
					case 2:
						animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y - 18.f);
						break;
					}
				}
				else
				{
					switch (g_ctx.globals.missed_shots[entity_index] % 3)
					{
					case 0:
						animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y - 38.f);
						break;
					case 1:
						animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y - 58.f);
						break;
					case 2:
						animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y - 18.f);
						break;
					}
				}
			}
			else
			{
				animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y);
			}
		}
	}*/


	if (slowwalk)
	{
		if (side == 1)
		{
			switch (g_ctx.globals.missed_shots[entity_index] % 3)
			{
			case 0:
				animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y - 24.f);
				break;
			case 1:
				animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y - 52.f);
				break;
			case 2:
				animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y - 38.f);
				break;
			}

			for (; animstate->m_flGoalFeetYaw > 180.0f; animstate->m_flGoalFeetYaw = animstate->m_flGoalFeetYaw - 360)
				;
			for (; animstate->m_flGoalFeetYaw < -180.0f; animstate->m_flGoalFeetYaw = animstate->m_flGoalFeetYaw + 360)
				;
		}
		else if (side == -1)
		{
			switch (g_ctx.globals.missed_shots[entity_index] % 5)
			{
			case 0:
				animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y + 24.f);
				break;
			case 1:
				animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y + 52.f);
				break;
			case 2:
				animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y + 38.f);
				break;
			}

			for (; animstate->m_flGoalFeetYaw > 180.0f; animstate->m_flGoalFeetYaw = animstate->m_flGoalFeetYaw - 360)
				;
			for (; animstate->m_flGoalFeetYaw < -180.0f; animstate->m_flGoalFeetYaw = animstate->m_flGoalFeetYaw + 360)
				;
		}
		else
		{
			animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y);

			for (; animstate->m_flGoalFeetYaw > 180.0f; animstate->m_flGoalFeetYaw = animstate->m_flGoalFeetYaw - 360)
				;
			for (; animstate->m_flGoalFeetYaw < -180.0f; animstate->m_flGoalFeetYaw = animstate->m_flGoalFeetYaw + 360)
				;
		}
	}
	else if (moving)
	{
		if (side == 1)
		{
			animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y - 10.f);

			for (; animstate->m_flGoalFeetYaw > 180.0f; animstate->m_flGoalFeetYaw = animstate->m_flGoalFeetYaw - 360)
				;
			for (; animstate->m_flGoalFeetYaw < -180.0f; animstate->m_flGoalFeetYaw = animstate->m_flGoalFeetYaw + 360)
				;
		}
		else if (side == -1)
		{
			animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y + 10.f);

			for (; animstate->m_flGoalFeetYaw > 180.0f; animstate->m_flGoalFeetYaw = animstate->m_flGoalFeetYaw - 360)
				;
			for (; animstate->m_flGoalFeetYaw < -180.0f; animstate->m_flGoalFeetYaw = animstate->m_flGoalFeetYaw + 360)
				;
		}
		else if (side == 0 || g_ctx.globals.missed_shots_reset[entity_index] == 1)
		{
			animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y);

			for (; animstate->m_flGoalFeetYaw > 180.0f; animstate->m_flGoalFeetYaw = animstate->m_flGoalFeetYaw - 360)
				;
			for (; animstate->m_flGoalFeetYaw < -180.0f; animstate->m_flGoalFeetYaw = animstate->m_flGoalFeetYaw + 360)
				;
		}
	}
	else if (jumping)
	{
		if (side == 1)
		{
			switch (g_ctx.globals.missed_shots[entity_index] % 4)
			{
			case 0:
				animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y - 13.f);
				break;
			case 1:
				animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y - 33.f);
				break;
			case 2:
				animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y - 53.f);
				break;
			case 3:
				animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y);
				break;
			}

			for (; animstate->m_flGoalFeetYaw > 180.0f; animstate->m_flGoalFeetYaw = animstate->m_flGoalFeetYaw - 360)
				;
			for (; animstate->m_flGoalFeetYaw < -180.0f; animstate->m_flGoalFeetYaw = animstate->m_flGoalFeetYaw + 360)
				;
		}
		else if (side == -1)
		{
			switch (g_ctx.globals.missed_shots[entity_index] % 4)
			{
			case 0:
				animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y + 13.f);
				break;
			case 1:
				animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y + 33.f);
				break;
			case 2:
				animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y + 53.f);
				break;
			case 3:
				animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y);
				break;
			}

			for (; animstate->m_flGoalFeetYaw > 180.0f; animstate->m_flGoalFeetYaw = animstate->m_flGoalFeetYaw - 360)
				;
			for (; animstate->m_flGoalFeetYaw < -180.0f; animstate->m_flGoalFeetYaw = animstate->m_flGoalFeetYaw + 360)
				;
		}
		else
		{
			animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y);

			for (; animstate->m_flGoalFeetYaw > 180.0f; animstate->m_flGoalFeetYaw = animstate->m_flGoalFeetYaw - 360)
				;
			for (; animstate->m_flGoalFeetYaw < -180.0f; animstate->m_flGoalFeetYaw = animstate->m_flGoalFeetYaw + 360)
				;
		}
	}
	else
	{
		if (side == 1)
		{
			if (!e->IsDormant())
			{

				switch (g_ctx.globals.missed_shots[entity_index] % 6)
				{
				case 0:
					animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y - v59);
					break;
				case 1:
					animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y - 24.f);
					break;
				case 2:
					animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y - 46.f);
					break;
				case 3:
					animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y - 58.f);
					break;
				case 4:
					animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y - 38.f);
					break;
				case 5:
					animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y - 12.f);
					break;
				}



				for (; animstate->m_flGoalFeetYaw > 180.0f; animstate->m_flGoalFeetYaw = animstate->m_flGoalFeetYaw - 360)
					;
				for (; animstate->m_flGoalFeetYaw < -180.0f; animstate->m_flGoalFeetYaw = animstate->m_flGoalFeetYaw + 360)
					;

			}
			else
			{

				switch (g_ctx.globals.missed_shots[entity_index] % 6)
				{
				case 0:
					animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y - v59);
					break;
				case 1:
					animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y - 24.f);
					break;
				case 2:
					animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y - 46.f);
					break;
				case 3:
					animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y - 58.f);
					break;
				case 4:
					animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y - 38.f);
					break;
				case 5:
					animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y - 12.f);
					break;
				}



				for (; animstate->m_flGoalFeetYaw > 180.0f; animstate->m_flGoalFeetYaw = animstate->m_flGoalFeetYaw - 360)
					;
				for (; animstate->m_flGoalFeetYaw < -180.0f; animstate->m_flGoalFeetYaw = animstate->m_flGoalFeetYaw + 360)
					;

			}
		}
		else if (side == -1)
		{
			if (!e->IsDormant())
			{

				switch (g_ctx.globals.missed_shots[entity_index] % 6)
				{
				case 0:
					animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y + v58);
					break;
				case 1:
					animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y + 24.f);
					break;
				case 2:
					animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y + 46.f);
					break;
				case 3:
					animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y + 58.f);
					break;
				case 4:
					animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y + 38.f);
					break;
				case 5:
					animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y + 12.f);
					break;
				}



				for (; animstate->m_flGoalFeetYaw > 180.0f; animstate->m_flGoalFeetYaw = animstate->m_flGoalFeetYaw - 360)
					;
				for (; animstate->m_flGoalFeetYaw < -180.0f; animstate->m_flGoalFeetYaw = animstate->m_flGoalFeetYaw + 360)
					;

			}
			else
			{

				switch (g_ctx.globals.missed_shots[entity_index] % 6)
				{
				case 0:
					animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y + v58);
					break;
				case 1:
					animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y + 24.f);
					break;
				case 2:
					animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y + 46.f);
					break;
				case 3:
					animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y + 58.f);
					break;
				case 4:
					animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y + 38.f);
					break;
				case 5:
					animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y + 12.f);
					break;
				}



				for (; animstate->m_flGoalFeetYaw > 180.0f; animstate->m_flGoalFeetYaw = animstate->m_flGoalFeetYaw - 360)
					;
				for (; animstate->m_flGoalFeetYaw < -180.0f; animstate->m_flGoalFeetYaw = animstate->m_flGoalFeetYaw + 360)
					;

			}
		}
		else
		{
			animstate->m_flGoalFeetYaw = math::normalize_yaw(e->m_angEyeAngles().y);

			for (; animstate->m_flGoalFeetYaw > 180.0f; animstate->m_flGoalFeetYaw = animstate->m_flGoalFeetYaw - 360)
				;
			for (; animstate->m_flGoalFeetYaw < -180.0f; animstate->m_flGoalFeetYaw = animstate->m_flGoalFeetYaw + 360)
				;
		}
	}

}
// le end
