#include<iostream>
#if 0
'''
#endif
int main(){
    std::printf("Happy mother's day!!!");
}
#if 0
'''
import pyglet as p
from pyglet.window import key
import logging
import random

# 全局花朵列表
flowers = []

def create_flower():
    """创建一朵花并设置其初始位置和动画"""
    global flowers
    
    flower_image = random.choice(["h1.png", "h2.png"])  # 随机选择花朵图片资源
    try:
        flower = p.sprite.Sprite(p.resource.image(flower_image))
        flower.scale = 0.5  # 调整花朵大小
        flower.x = random.randint(0, win.width - flower.width)  # 随机水平位置
        flower.y = win.height  # 初始垂直位置在屏幕顶部

        flowers.append(flower)  # 添加到全局花朵列表

        def update_flower(dt):
            """更新花朵位置，使其缓慢移动到屏幕底部"""
            flower.y -= 100 * dt  # 增加速度以便更容易看到效果
            if flower.y < -flower.height:  # 如果花朵移出屏幕底部，则删除
                flowers.remove(flower)
                p.clock.unschedule(update_flower)

        p.clock.schedule_interval(update_flower, 1/60.0)  # 每帧更新花朵位置
        return flower
    except Exception as e:
        return None


def draw_text(t, tx, ty, fn="HarmonyOS Sans SC", fs=20):
    try:
        label = p.text.Label(
            t,
            font_name=fn,
            font_size=fs,
            x=tx,
            y=ty,
            anchor_x="center",
            anchor_y="center"
        )
    except AssertionError:
        logging.warning("字体文件不存在，已切换为系统默认字体")
        fn = "Microsoft YaHei"
        label = p.text.Label(
            t,
            font_name=fn,
            font_size=fs,
            x=tx,
            y=ty,
            anchor_x="center",
            anchor_y="center"
        )
    except Exception as e:
        logging.error(e)
    return label


def main():
    global label, win, flowers
    
    # 初始化花朵列表
    flowers = []

    win = p.window.Window(1000, 1000, caption="❤️母亲节快乐❤️")

    win.set_mouse_visible(visible=False)
    
    p.resource.path = ["./imgs"]
    p.resource.reindex()

    try:
        image = p.resource.image("bg.png")
        
        image_width, image_height = image.width, image.height
        
        scale_x = win.width / image_width
        scale_y = win.height / image_height
        scale = min(scale_x, scale_y)
        
        image.width = int(image_width * scale)
        image.height = int(image_height * scale)
        
        image_x = (win.width - image.width) // 2
        image_y = (win.height - image.height) // 2
        
        label = draw_text("🎇母亲节快乐❤️", win.width // 2, win.height // 2, fs=50)
        
        @win.event
        def on_draw():
            win.clear()
            if image:
                image.blit(image_x, image_y)
            # 绘制所有花朵
            for flower in flowers:
                flower.draw()
            label.draw()
            
        @win.event
        def on_key_press(symbol, modifiers):
            """处理按键事件，按下 H 键时生成花朵"""
            if symbol == key.H:
                num_flowers = random.randint(7, 15)  # 随机生成 7 到 15 朵花
                for _ in range(num_flowers):
                    create_flower()

    except Exception as e:
        logging.error(f"图片加载失败: {e}")
        label = draw_text("图片加载失败，请检查资源路径", win.width // 2, win.height // 2)
        
        @win.event
        def on_draw():
            win.clear()
            # 绘制所有花朵
            for flower in flowers:
                flower.draw()
            label.draw()
            
        @win.event
        def on_key_press(symbol, modifiers):
            """处理按键事件，按下 H 键时生成花朵"""
            if symbol == key.H:
                num_flowers = random.randint(7, 15)  # 随机生成 7 到 15 朵花
                for _ in range(num_flowers):
                    create_flower()

    p.app.run()

if __name__ == "__main__":
    main()
#endif