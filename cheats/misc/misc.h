#include "..\..\includes.hpp"

class misc : public singleton <misc>
{
public:
	void watermark();
	void NoDuck(CUserCmd* cmd);
	void edgebug(CUserCmd* pCmd);
	void jumpbug(CUserCmd* pCmd);
	void ChangeRegion();
	void ChatSpamer();
	void NameSpam();
	void AutoCrouch(CUserCmd* cmd);
	void SlideWalk(CUserCmd* cmd);
	void automatic_peek(CUserCmd* cmd, float wish_yaw);
	void ViewModel();
	void FullBright();
	void PovArrows(player_t* e, Color color);
	void NightmodeFix();
	void zeus_range();
	void desync_arrows();
	void aimbot_hitboxes();
	void ragdolls();
	void rank_reveal();
	void fast_stop(CUserCmd* m_pcmd);
	void spectators_list();
	void backgrounds();
	void minigames();
	bool double_tap(CUserCmd* m_pcmd);
	void hide_shots(CUserCmd* m_pcmd, bool should_work);
	bool can_shift_shot(int ticks);


	bool recharging_double_tap = false;

	bool double_tap_enabled = false;
	bool double_tap_key = false;
	bool has_double_tapped_lol = false;

	bool hide_shots_enabled = false;
	bool hide_shots_key = false;
};