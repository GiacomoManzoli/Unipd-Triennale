<?php 

function connect(&$con){
	$development  = true;
	if ($development){
		$conn=mysql_connect('localhost', 'root', '123456') 
			or err('Connessione a mysql fallita'); 
		mysql_select_db('prenotazioni_cinema');
	}
	else{
		$conn=mysql_connect('localhost', 'gmanzoli', '1niG3fBl') 
			or err('Connessione a mysql fallita'); 
		mysql_select_db('gmanzoli-PR');
	}
}

?>