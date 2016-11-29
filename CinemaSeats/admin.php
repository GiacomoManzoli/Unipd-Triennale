<?php
require_once('./support/_components.php');

$autorizzato=startPage("Amministrazione",3);

if ($autorizzato){
	drawLogo();
	drawUserbar(4);

	drawAdminBar(0);

	echo '<div class="row"><div class="col-md-12">';

	echo '<h3>Benvenuto</h3>';
	echo '<p>Da questo pannello potrai amministrare il cinema, per iniziare seleziona una categoria dal menu\' sovrastante.</p>';

	echo '</div></div>';
}
endPage();

?>