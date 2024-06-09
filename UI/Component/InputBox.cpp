#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro.h>
#include <memory>
#include "Engine/IObject.hpp"
#include "Label.hpp"
#include "InputBox.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"
#include <iostream>

namespace Engine {
    InputBox::InputBox(const std::string& font, int fontSize, float x, float y, float w, float h, float r, float g, float b, float a, float br, float bg, float bb, float ba, bool isPassword, std::string info, float anchorX, float anchorY) :
        IObject(x, y, w, h, anchorX, anchorY), 
        //label("", font, fontSize, Position.x - Anchor.x * Size.x+x/2, y, r, g, b, a, 0, 0), 
        backgroundColor(al_map_rgba(br, bg, bb, ba)), 
        textColor(al_map_rgba(r, g, b, a)), 
        borderColor(al_map_rgba(r, g, b, a)),
        isPassword(isPassword),info(info),
        text(""){
            fontPtr = Resources::GetInstance().GetFont(font, fontSize);
            fontSmall = Resources::GetInstance().GetFont(font, 23);
            //fontPtr = allegro_font
    }

    void InputBox::Draw() const {
        // Draw the background rectangle
        //al_draw_filled_rectangle(Position.x - Anchor.x * Size.x, Position.y - Anchor.y * Size.y, Position.x + (1 - Anchor.x) * Size.x, Position.y + (1 - Anchor.y) * Size.y, backgroundColor);
        // Draw the border rectangle
        al_draw_rectangle(Position.x - Anchor.x * Size.x, Position.y - Anchor.y * Size.y, Position.x + (1 - Anchor.x) * Size.x, Position.y + (1 - Anchor.y) * Size.y, borderColor, 2);
        // Draw the label text
        std::string displayText = isPassword ? std::string(text.length(), '*' ) : text;
        al_draw_text(fontPtr.get(), textColor, Position.x - Anchor.x * Size.x + 5, Position.y - Anchor.y * Size.y+10, 0, displayText.c_str());
        if(!focused && text == ""){
            char arr[100];
            int len = info.size();
            for(int i = 0 ; i < len ; i++){
                arr[i] = info[i];
            }
            arr[len] = '\0';
            al_draw_text(fontSmall.get(), al_map_rgba(255,255,255,70), Position.x - Anchor.x * Size.x + 5, Position.y - Anchor.y * Size.y+10, 0, arr);
        }
    }


    void InputBox::SetText(const std::string& text) {
        //label.Text = text;
    }
    void InputBox::OnKeyDown(int keyCode) {
        //std::cout << keyCode << "\n";
        if(focused){
            if ((keyCode >= ALLEGRO_KEY_A && keyCode <= ALLEGRO_KEY_Z) || (keyCode >= ALLEGRO_KEY_0 && keyCode <= ALLEGRO_KEY_9)) {
                char ch;
                if (keyCode >= ALLEGRO_KEY_A && keyCode <= ALLEGRO_KEY_Z) {
                    ch = 'a' + (keyCode - ALLEGRO_KEY_A);
                } else {
                    ch = '0' + (keyCode - ALLEGRO_KEY_0);
                }
                text += ch;
                SetText(text);
            } else if (keyCode == ALLEGRO_KEY_BACKSPACE && !text.empty()) {
                text.pop_back();
                SetText(text);
            }
            std::cout << text << "\n";
            Draw();
        }
    }
    void InputBox::OnMouseDown(int button, int mx, int my) {
        if (mx >= Position.x - Anchor.x * Size.x && mx <= Position.x + (1 - Anchor.x) * Size.x &&
            my >= Position.y - Anchor.y * Size.y && my <= Position.y + (1 - Anchor.y) * Size.y) {
            focused = true;
        } else {
            focused = false;
        }
    }

    const std::string& InputBox::GetText() const {
        return text;
    }
    void InputBox::TogglePasswordMode() {
        isPassword = !isPassword;
    }
}
