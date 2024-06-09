#ifndef INPUTBOX_HPP
#define INPUTBOX_HPP

#include "Engine/IControl.hpp"
#include "Engine/IObject.hpp"
#include "Label.hpp"
#include <string>
#include <memory>

namespace Engine {
    class InputBox : public IControl, public IObject {
    private:
        //Label label;
        std::string text;
        ALLEGRO_COLOR backgroundColor;
        ALLEGRO_COLOR textColor;
        ALLEGRO_COLOR borderColor;
        std::shared_ptr<ALLEGRO_FONT> fontPtr;
        std::shared_ptr<ALLEGRO_FONT> fontSmall;
        std::string info; 
        bool focused;
        bool isPassword;
    public:
        InputBox(const std::string& font, int fontSize, float x, float y, float w, float h,
                float r, float g, float b, float a,
                float br, float bg, float bb, float ba, bool isPassword, std::string info,
                float anchorX = 0.5f, float anchorY = 0.5f);

        // 重写 IControl 中的事件处理函数
        void OnKeyDown(int keyCode) override;
        void OnMouseDown(int button, int mx, int my) override;

        // 重写 IObject 中的绘制函数
        void Draw() const override;

        // 其他方法，用于获取和设置文本内容等
        const std::string& GetText() const;
        void SetText(const std::string& newText);
        void TogglePasswordMode();
    };
}

#endif // INPUTBOX_HPP