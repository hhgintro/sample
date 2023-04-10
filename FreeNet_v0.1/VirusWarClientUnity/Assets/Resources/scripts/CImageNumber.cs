using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class CImageNumber : MonoBehaviour {

	List<Texture> images;
	int width;

	void Awake()
	{
		this.images = new List<Texture>();
		for (int i = 0; i <= 9; ++i)
		{
			Texture texture = Resources.Load(string.Format("images/n{0:D2}", i)) as Texture;
			this.images.Add(texture);
		}

		this.width = this.images[0].width;
	}

	public void print(int number, float x, float y, float ratio)
	{
		string number_string = string.Format("{0:22}", number.ToString("D2"));
		for (int i = 0; i < number_string.Length; ++i)
		{
			string digit = number_string.Substring(i, 1);
			print_texture(int.Parse(digit), x, y, ratio);
			x += this.width;
		}
	}

	void print_texture(int texture_index, float x, float y, float ratio)
	{
		Texture target = this.images[texture_index];
		GUI.DrawTexture(new Rect(x, y, target.width * ratio, target.height * ratio), target);
	}
}
