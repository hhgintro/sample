using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class CBattleInfoPanel : MonoBehaviour {

	List<Texture> turn_info;
	int width;
	int height;

	Texture myteam_mark;
	Texture otherteam_mark;

	void Awake()
	{
		this.turn_info = new List<Texture>();
		this.turn_info.Add(Resources.Load("images/red_playing") as Texture);
		this.turn_info.Add(Resources.Load("images/blue_playing") as Texture);

		this.width = this.turn_info[0].width;
		this.height = this.turn_info[0].height;

		this.myteam_mark = Resources.Load("images/me") as Texture;
		this.otherteam_mark = Resources.Load("images/other") as Texture;
	}

	public void draw_turn_info(int player_index, float ratio)
	{
		Texture texture = this.turn_info[player_index];

		Rect rect;
		if (player_index == 0)
		{
			rect = new Rect(0, 0, this.width * ratio, this.height * ratio);
		}
		else
		{
			rect = new Rect(Screen.width - width * ratio, 0, this.width * ratio, this.height * ratio);
		}

		GUI.DrawTexture(rect, texture);
	}


	public void draw_myinfo(int player_me_index, float ratio)
	{
		Rect rect_me;
		Rect rect_other;
		if (player_me_index == 0)
		{
			rect_me = new Rect(0, this.height * ratio, this.myteam_mark.width * ratio, this.myteam_mark.height * ratio);
			rect_other = new Rect(Screen.width - this.otherteam_mark.width * ratio, this.height * ratio, this.otherteam_mark.width * ratio, this.otherteam_mark.height * ratio);
		}
		else
		{
			rect_me = new Rect(Screen.width - this.myteam_mark.width * ratio, this.height * ratio, this.myteam_mark.width * ratio, this.myteam_mark.height * ratio);
			rect_other = new Rect(0, this.height * ratio, this.otherteam_mark.width * ratio, this.otherteam_mark.height * ratio);
		}

		GUI.DrawTexture(rect_me, this.myteam_mark);
		GUI.DrawTexture(rect_other, this.otherteam_mark);
	}
}
