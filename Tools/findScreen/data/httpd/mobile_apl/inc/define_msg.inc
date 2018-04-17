<?php
//////////////////////////////////////////////
//
// エラーメッセージ定義
//
//////////////////////////////////////////////
// ------------------------------------------------------------
// 2008/08/28 matsukawa   $D_ERR_NOTFOUNDを検索種類毎に分ける
//                        メッセージをカスタマイズ可能にする
// ------------------------------------------------------------
if(!isset($D_ERR_NOTFOUND))     $D_ERR_NOTFOUND     = "該当する@WORD@が存在しません。<BR>戻るボタンで戻り、<BR>再度検索を行って下さい。";
if(!isset($D_ERR_NOTFOUND_A))   $D_ERR_NOTFOUND_A   = "該当する@WORD@が存在しません。<BR>戻るボタンで戻り、<BR>再度検索を行って下さい。";
if(!isset($D_ERR_NOTFOUND_E))   $D_ERR_NOTFOUND_E   = "該当する@WORD@が存在しません。<BR>戻るボタンで戻り、<BR>再度検索を行って下さい。";
if(!isset($D_ERR_NOTFOUND_C))   $D_ERR_NOTFOUND_C   = "該当する@WORD@が存在しません。<BR>戻るボタンで戻り、<BR>再度検索を行って下さい。";
if(!isset($D_ERR_NOTFOUND_Z))   $D_ERR_NOTFOUND_Z   = "該当する@WORD@が存在しません。<BR>戻るボタンで戻り、<BR>再度検索を行って下さい。";
if(!isset($D_ERR_NOTFOUND_N))   $D_ERR_NOTFOUND_N   = "該当する@WORD@が存在しません。<BR>戻るボタンで戻り、<BR>再度検索を行って下さい。";
if(!isset($D_ERR_NOTFOUND_NE))  $D_ERR_NOTFOUND_NE  = "該当する@WORD@が存在しません。<BR>戻るボタンで戻り、<BR>再度検索を行って下さい。";
if(!isset($D_ERR_KEYWORD))      $D_ERR_KEYWORD      = "キーワードが入力されていません。<BR>入力後再度検索を行って下さい。";
if(!isset($D_ERR_ZIPCODE))      $D_ERR_ZIPCODE      = "郵便番号の指定が正しくありません。<BR>半角数値７桁を入力して下さい。";
if(!isset($D_ERR_PARAMETER))    $D_ERR_PARAMETER    = "サーバーが混雑している可能性があります。<BR>時間をおいて再度検索を行って下さい。";
if(!isset($D_ERR_LIMITCHK))     $D_ERR_LIMITCHK     = "期限が切れているかパラメータが無効です。<BR>戻るボタンで戻って下さい。";
if(!isset($D_ERR_DMS))          $D_ERR_DMS          = "パラメータの指定が無効です。<BR>表示できません。";
if(!isset($D_NOT_CPNT))         $D_NOT_CPNT         = "該当する@WORD@が存在しません。";
if(!isset($D_ERR_ROUTE))        $D_ERR_ROUTE        = "指定場所までの距離が遠いため、ルートを表示できません。<BR>戻るボタンで戻って下さい。";
?>
