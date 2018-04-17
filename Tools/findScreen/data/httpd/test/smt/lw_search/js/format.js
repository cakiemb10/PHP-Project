$(document).ready(function(){
//読み込み時の表示
window_load();
//ウィンドウサイズ変更時に更新
window.onresize = window_load;

function window_load() {
    Calculation();
    $(".ic_wp li img").css({
        "width": w_a + "px",
    });
    $(".ic_wp2 li img").css({
        "width": w_p + "px",
    });
    $(".main_box").css({
        "width": w_b + "px",
    });
    $(".main_box h2").css({
        "font-size": w_c + "px",
        "padding-left": w_h + "px",
    });

    $(".box_txt").css({
        "font-size": w_e + "px"
    });
    $(".box_txt02").css({
        "font-size": w_e * 1.1 + "px"
    });
    $(".box_head").css({
        "background-size": w_f + "px " + w_f + "px",
        "-webkit-background-size": w_f + "px " + w_f + "px",
    });    
    $(".ic_wp").css({
        "width": w_g + "px",
    });
    $(".box_sub,.box_sub02").css({
        "width": w_g + "px",
    });
    
    $(".bt img").css({
        "width": w_b + "px",
    });
    $(".box_tel").css({
        "width": w_g * 0.5 + "px",
    });
};
});