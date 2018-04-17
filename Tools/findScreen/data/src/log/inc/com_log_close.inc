<?php
//debug
// mod 2011/07/05 Y.Nakajima [
//LoggerNDC::clear();
//LoggerManager::shutdown();

$LoggerNDC = new LoggerNDC();
$LoggerNDC->clear();
$LoggerManager = new LoggerManager();
$LoggerManager->shutdown();

// mod 2011/07/05 Y.Nakajima ]

?>
