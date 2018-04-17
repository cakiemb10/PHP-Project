$(document).ready(function(){
openTarget();
checkStyle();
setupDes();
//読み込み時の表示
window_load();
//ウィンドウサイズ変更時に更新
window.onresize = window_load;
function window_load() {
    Calculation();
    $(".bt img").css({
        "width": w_i + "px",
    });
    $(".search").css({
        "width": w_i + "px",
    });
    $("#title").css({
        "width": w_i + "px",
    });
    $(".menu").css({
        "width": w_ii + "px",
    });
    $(".imagesbtn").css({
        "width": w_j + "px",
        "height": h_a + "px",
    });
    $("#search").css({
        "width": w_k + "px",
        "height": h_a + "px",
        "background-size": w_k + "px " + h_a + "px",
        "-webkit-background-size": w_k + "px " + h_a + "px",
        "font-size": w_l + "px ",
    });
    $(".menu .title img,.menu div").css({
        "width": w_g + "px",
    });
    $(".kensaku input").css({
        "width": w_g + "px",
    });
    $(".td01").css({
        "width": w_m + "px",
    });
    $(".td01_2").css({
        "width": w_r + "px",
    });
    $(".td01 img").css({
        "width": w_f + "px",
    });
    $(".td01_2 img").css({
        "width": w_q + "px",
    });
    $(".td02").css({
        "font-size": w_l + "px",
        "line-height": w_l + "px",
        "width": w_n + "px",
    });
}
function openTarget(){
    /* 開く・閉じる*/
    $(".menu").hide();
    $("div#title").click(function(){
        if($('div#title img').attr("src") == "images/bt_03_on.jpg"){
           $('div#title img').attr("src","images/bt_03.png");
        }else if ($('div#title img').attr("src") == "images/bt_03.png"){
            $('div#title img').attr("src","images/bt_03_on.jpg");
        }
        $(this).next().toggle();
    });
};
function checkStyle(){
     $(".data tr").click(function(){
        var chkB = $(this).find("td").children("input[type=checkbox]");
        if(chkB.attr("checked")) {
            chkB.attr('checked', false);
            chkB.removeClass('chkflg');
        }else{
            chkB.attr('checked', true);
            chkB.addClass('chkflg');
        }
    });
    $("td input[type=checkbox]").click(function(){
        if($(this).attr("checked")) {
            $(this).attr('checked', false);
        }else{
            $(this).attr('checked', true);
        }
    });
     $(".data tr").click(function(){
        var chkB = $(this).find("td").children("input[type=radio]");
        if(chkB.attr("checked")) {
            chkB.attr('checked', false);
            chkB.removeClass('chkflg');
        }else{
            chkB.attr('checked', true);
            chkB.addClass('chkflg');
        }
    });
    $("td input[type=radio]").click(function(){
        if($(this).attr("checked")) {
            $(this).attr('checked', false);
        }else{
            $(this).attr('checked', true);
        }
    });
};
//INPUT の初期値をクリックで消す
function setupDes() {
    // 種付け作業
    var textarea = document.getElementsByTagName("textarea");
    for (i = 0; i < textarea.length; i++) {
        if (textarea[i].className.search("nodes") < 0) {
            if (textarea[i].value == textarea[i].defaultValue) {textarea[i].className += " ondes"; }
            textarea[i].onfocus = function() {offDes(this); }
            textarea[i].onblur = function() {onDes(this); }
        }
    }
    var input = document.getElementsByTagName("input");
    for (i = 0; i < input.length; i++) {
        if ((input[i].className.search("nodes") < 0) && ((input[i].getAttribute("type") == "text")||(input[i].getAttribute("type") == null))) {
            if (input[i].value == input[i].defaultValue) {input[i].className += " ondes"; }
            input[i].onfocus = function() {offDes(this); }
            input[i].onblur = function() {onDes(this); }
        }
    }
    return;
}
function offDes(from) {
    if (from.className.search("ondes") < 0) {return 0;}
    from.className = from.className.replace(/ondes/, "");
    from.value = "";
    return 1;
}
function onDes(from) {
    if (from.value != "") {return 0;}
    from.className += " ondes";
    from.value = from.defaultValue;
    return 1;
}

});
