<?php
require_once('./support/_components.php');
require_once('./support/_various.php');

logout();
startPage("Log out",0);
drawLogo();

drawMsg("success","Log out effettuato con successo, torna presto a trovarci");

endPage();

?>