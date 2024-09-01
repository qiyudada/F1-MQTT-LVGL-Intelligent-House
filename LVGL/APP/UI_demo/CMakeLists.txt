SET(SOURCES screens/ui_Message.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    ui_events.c
    images/ui_img_weather_1_png.c
    images/ui_img_time_png.c
    images/ui_img_iu_png.c
    images/ui_img_dark_png.c
    images/ui_img_bg1_png.c
    images/ui_img_bg4_png.c
    ui_temporary_image.c
    fonts/ui_font_Number.c)

add_library(ui ${SOURCES})
