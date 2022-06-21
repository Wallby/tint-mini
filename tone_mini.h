/*
MIT No Attribution

Copyright 2022 Martinus Theodorus Johannes Helena ten Velden

Permission is hereby granted, free of charge, to any person obtaining a copy of this
software and associated documentation files (the "Software"), to deal in the Software
without restriction, including without limitation the rights to use, copy, modify,
merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef TONE_MINI_H
#define TONE_MINI_H

#define TM_FUNCTION static

#include <math.h>


struct tm_tone_t
{
	float color; //< 0.0 (red) <= color < 360.0, 60.0 == yellow, 120.0 == green, 180.0 == cyan, 240.0 == blue, 300.0 == magenta
	float saturation; //< 0.0 <= saturation <= 1.0
	float tone; //< -1.0 (black) <= tone <= +1.0 (white) <- -1.0 and +1.0 mapping is arbitrary
};
// NOTE: tm_tone_black does not require color nor saturation thus both are undefined
static const struct tm_tone_t tm_tone_black = { .tone = -1.0f };
// NOTE: tm_tone_gray does not require color thus is undefined
static const struct tm_tone_t tm_tone_gray = { .saturation = 0.0f, .tone = 0.5f };
// NOTE: tm_tone_white does not require color not saturation thus both are undefined
static const struct tm_tone_t tm_tone_white = { .tone = +1.0f };
static const struct tm_tone_t tm_tone_red = { .color = 0.0f, .saturation = 1.0f, .tone = 0.0f };
static const struct tm_tone_t tm_tone_green = { .color = 120.0f, .saturation = 1.0f, .tone = 0.0f };
static const struct tm_tone_t tm_tone_blue = { .color = 240.0f, .saturation = 1.0f, .tone = 0.0f };
static const struct tm_tone_t tm_tone_darkred = { .color = 0.0f, .saturation = 1.0f, .tone = -0.5f };
static const struct tm_tone_t tm_tone_lightred = { .color = 0.0f, .saturation = 1.0f, .tone = +0.5f };
static const struct tm_tone_t tm_tone_darkgreen = { .color = 120.0f, .saturation = 1.0f, .tone = -0.5f };
static const struct tm_tone_t tm_tone_lightgreen = { .color = 120.0f, .saturation = 1.0f, .tone = +0.5f };
static const struct tm_tone_t tm_tone_darkblue = { .color = 240.0f, .saturation = 1.0f, .tone = -0.5f };
static const struct tm_tone_t tm_tone_lightblue = { .color = 240.0f, .saturation = 1.0f, .tone = +0.5f };

// NOTE: tint is e.g. for light where adding lightens
struct tm_tint_t
{
	float color; //< 0.0 <= color < 360.0
	float saturation; //< 0.0 <= saturation <= 1.0
	float tint; //< 0.0 (black) <= tint <= 1.0 (white)
};
static const struct tm_tint_t tm_tint_black = { .tint = 0.0f };
static const struct tm_tint_t tm_tint_gray = { .saturation = 0.0f, .tint = 0.5f };
static const struct tm_tint_t tm_tint_white = { .tint = 1.0f };

struct tm_tintrgb_t
{
	float r;
	float g;
	float b;
};
static const struct tm_tintrgb_t tm_tintrgb_black = { .r = 0.0f, .g = 0.0f, .b = 0.0f };
static const struct tm_tintrgb_t tm_tintrgb_gray = { .r = 0.5f, .g = 0.5f, .b = 0.5f };
static const struct tm_tintrgb_t tm_tintrgb_white = { .r = 1.0f, .g = 1.0f, .b = 1.0f };

struct tm_tintcmy_t
{
	float c;
	float m;
	float y;
};
static const struct tm_tintcmy_t tm_tintcmy_black = { .c = 0.0f, .m = 0.0f, .y = 0.0f };
static const struct tm_tintcmy_t tm_tintcmy_gray = { .c = 0.5f, .m = 0.5f, .y = 0.5f };
static const struct tm_tintcmy_t tm_tintcmy_white = { .c = 1.0f, .m = 1.0f, .y = 1.0f };

// NOTE: shade is e.g. for a print on a white background where adding darkens
struct tm_shade_t
{
	float color; //< 0.0 <= color <= 360.0
	float saturation; //< 0.0 <= saturation <= 1.0
	float shade; //< 0.0 (white) <= shade <= 1.0 (black)
};
static const struct tm_shade_t tm_shade_black = { .shade = 1.0f };
static const struct tm_shade_t tm_shade_gray = { .saturation = 0.0f, .shade = 0.5f };
static const struct tm_shade_t tm_shade_white = { .shade = 0.0f };

struct tm_shadergb_t
{
	float r;
	float g;
	float b;
};
static const struct tm_shadergb_t tm_shadergb_black = { .r = 1.0f, .g = 1.0f, .b = 1.0f };
static const struct tm_shadergb_t tm_shadergb_gray = { .r = 0.5f, .g = 0.5f, .b = 0.5f };
static const struct tm_shadergb_t tm_shadergb_white = { .r = 0.0f, .g = 0.0f, .b = 0.0f };

struct tm_shadecmy_t
{
	float c;
	float m;
	float y;
};
static const struct tm_shadecmy_t tm_shadecmy_black = { .c = 1.0f, .m = 1.0f, .y = 1.0f };
static const struct tm_shadecmy_t tm_shadecmy_gray = { .c = 0.5f, .m = 0.5f, .y = 0.5f };
static const struct tm_shadecmy_t tm_shadecmy_white = { .c = 0.0f, .m = 0.0f, .y = 0.0f };

//*****************************************************************************

// NOTE: tm_rgb_t is only for representing color (i.e. "saturation == 1.0f &..
//       .. tone == 0.0f")
//       ^
//       thus impossible.. e.g. dark red, light red, less saturated red
struct tm_rgb_t
{
	float r;
	float g;
	float b;
};
// NOTE: tm_cmy_t is only for representing color (i.e. "saturation == 1.0f &..
//       .. tone == 0.0f")
//       ^
//       thus impossible.. e.g. dark cyan, light cyan, less saturated cyan
struct tm_cmy_t
{
	float c;
	float m;
	float y;
};

// NOTE: if color == 0.0f.. returns { .r == 1.0f, .g = 0.0f, .b = 0.0f }
//       if color == 60.0f.. returns { .r = 0.5f, .g = 0.5f, .b = 0.0f }
//       .
//       .
//       .
// NOTE: assumes 0.0 <= color < 360.0
TM_FUNCTION struct tm_rgb_t tm_color_to_rgb(float color)
{
	struct tm_rgb_t rgb;

	// 1. calculate distance from r/g/b as..
	//    .. 0.0f == no r/g/b
	//    .. 0.5f == 50% between r-g/g-b/b-r
	//    .. 1.0f == at r/g/b
	float a = 1.0f - (fminf(color, 120.0f) / 120.0f); //< "+r"
	float b = 1.0f - ((360.0f - fmaxf(240.0f, color)) / 120.0f); //< "-r"
	//rgb.r = fmaxf(a, b);
	rgb.r = a + b;
	rgb.g = 1.0f - fabsf((fminf(color, 240.0f) - 120.0f) / 120.0f);
	rgb.b = 1.0f - fabsf((fmaxf(color, 120.0f) - 240.0f) / 120.0f);

	// 2. if r/g/b >= 0.5f.. r/g/b == 1.0f, otherwise.. r/g/b *= 2.0f
	
	rgb.r = rgb.r >= 0.5f ? 1.0f : rgb.r * 2.0f;
	rgb.g = rgb.g >= 0.5f ? 1.0f : rgb.g * 2.0f;
	rgb.b = rgb.b >= 0.5f ? 1.0f : rgb.b * 2.0f;

	return rgb;
}

//*****************************************************************************

TM_FUNCTION struct tm_tint_t tm_tone_to_tint(struct tm_tone_t tone)
{
	struct tm_tint_t tint;
	tint.color = tone.color;
	tint.saturation = tone.saturation;
	tint.tint = (tone.tone / 2.0f) + 0.5f;
	return tint;
}
TM_FUNCTION struct tm_tone_t tm_tint_to_tone(struct tm_tint_t tint)
{
	struct tm_tone_t tone;
	tone.color = tint.color;
	tone.saturation = tint.saturation;
	tone.tone = (tint.tint - 0.5f) * 2.0f;
	return tone;
}
// NOTE: not sure if 100% correct
TM_FUNCTION struct tm_tintrgb_t tm_tone_to_tintrgb(struct tm_tone_t tone)
{
	//shadef("tone.color %f tone.saturation %f tone.tone %f\n", tone.color, tone.saturation, tone.tone);

	// 1. color from tone w.o. saturation nor tone

	struct tm_rgb_t rgb = tm_color_to_rgb(tone.color);
	
	//shadef("rgb.r %f rgb.g %f rgb.b %f\n", rgb.r, rgb.g, rgb.b);
	
	// 2. apply saturation (i.e. lerp(rgb, tintrgb_gray, tone.saturation)..?)
	
	struct tm_tintrgb_t tintrgb;
	tintrgb.r = tone.saturation * rgb.r + (1.0f - tone.saturation) * 0.5f;
	tintrgb.g = tone.saturation * rgb.g + (1.0f - tone.saturation) * 0.5f;
	tintrgb.b = tone.saturation * rgb.b + (1.0f - tone.saturation) * 0.5f;
	
	//shadef("tintrgb.r %f tintrgb.g %f tintrgb.b %f\n", tintrgb.r, tintrgb.g, tintrgb.b);
	
	// 3. apply tone
	
	// if tone.tone > 0.0f.. lerp(rgb, tintrgb_white, tone.tone)
	if(tone.tone > 0.0f)
	{
		tintrgb.r = tintrgb.r * (1.0f - tone.tone) + 1.0f * tone.tone;
		tintrgb.g = tintrgb.g * (1.0f - tone.tone) + 1.0f * tone.tone;
		tintrgb.b = tintrgb.b * (1.0f - tone.tone) + 1.0f * tone.tone;
	}
	// if tone.tone < 0.5f.. lerp(tintrgb, tintrgb_black, -tone.tone)
	if(tone.tone < 0.0f)
	{
		tintrgb.r = tintrgb.r * (1.0f - (-tone.tone));
		tintrgb.g = tintrgb.g * (1.0f - (-tone.tone));
		tintrgb.b = tintrgb.b * (1.0f - (-tone.tone));
	}
	
	//shadef("tintrgb.r %f tintrgb.g %f tintrgb.b %f\n", tintrgb.r, tintrgb.g, tintrgb.b);
	
	return tintrgb;
};
TM_FUNCTION struct tm_tintrgb_t tm_tint_to_tintrgb(struct tm_tint_t tint)
{
	struct tm_tone_t tone = tm_tint_to_tone(tint);
	return tm_tone_to_tintrgb(tone);
}

TM_FUNCTION struct tm_shade_t tm_tone_to_shade(struct tm_tone_t tone)
{
	struct tm_shade_t shade;
	shade.color = tone.color;
	shade.saturation = tone.saturation;
	shade.shade = ((-tone.tone) / 2.0f) + 0.5f;
}
TM_FUNCTION struct tm_tone_t tm_shade_to_tone(struct tm_shade_t shade)
{
	struct tm_tone_t tone;
	tone.color = shade.color;
	tone.saturation = shade.saturation;
	tone.tone = -((shade.shade - 0.5f) * 2.0f);
	return tone;
}
TM_FUNCTION struct tm_shadergb_t tm_tone_to_shadergb(struct tm_tone_t tone)
{
	tone.tone = -tone.tone;
	struct tm_tintrgb_t a = tm_tone_to_tintrgb(tone); //< not actually tintrgb as above tone.tone = -tone.tone
	struct tm_shadergb_t shadergb = { .r = a.r, .g = a.g, .b = a.b };
	return shadergb;
}
TM_FUNCTION struct tm_shadergb_t tm_shade_to_shadergb(struct tm_shade_t shade)
{
	struct tm_tone_t tone = tm_shade_to_tone(shade);
	return tm_tone_to_shadergb(tone);
}

TM_FUNCTION struct tm_shade_t tm_tint_to_shade(struct tm_tint_t tint)
{
	struct tm_shade_t shade;
	shade.color = tint.color;
	shade.saturation = tint.saturation;
	shade.shade = 1.0f - tint.tint;
	return shade;
}
TM_FUNCTION struct tm_shadergb_t tm_tintrgb_to_shadergb(struct tm_tintrgb_t tintrgb)
{
	struct tm_shadergb_t shadergb;
	shadergb.r = 1.0f - tintrgb.r;
	shadergb.g = 1.0f - tintrgb.g;
	shadergb.b = 1.0f - tintrgb.b;
	return shadergb;
}
TM_FUNCTION struct tm_tint_t tm_shade_to_tint(struct tm_shade_t shade)
{
	struct tm_tint_t tint;
	tint.color = shade.color;
	tint.saturation = shade.saturation;
	tint.tint = 1.0f - shade.shade;
	return tint;
}
TM_FUNCTION struct tm_tintrgb_t tm_shadergb_to_tintrgb(struct tm_shadergb_t shadergb)
{
	struct tm_tintrgb_t tintrgb;
	tintrgb.r = 1.0f - shadergb.r;
	tintrgb.g = 1.0f - shadergb.g;
	tintrgb.b = 1.0f - shadergb.b;
	return tintrgb;
}

#endif
