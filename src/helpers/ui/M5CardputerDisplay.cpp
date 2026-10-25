#include "M5CardputerDisplay.h"

// Implementation file for M5CardputerDisplay
// Most functionality is inline in the header for efficiency

// Color scheme
ColorVal UIColor::window_bkg = TFT_BLACK;
ColorVal UIColor::title_bkg = TFT_BLUE;
ColorVal UIColor::title_txt = TFT_WHITE;
ColorVal UIColor::primary_txt = TFT_WHITE;
ColorVal UIColor::secondary_txt = (18 << 11) | (36 << 5) | 18;  // mid-gray
ColorVal UIColor::warning_txt = TFT_ORANGE;
ColorVal UIColor::popup_bkg = TFT_CYAN;
ColorVal UIColor::popup_txt = TFT_BLACK;
ColorVal UIColor::corp_blue = 0x001A;
