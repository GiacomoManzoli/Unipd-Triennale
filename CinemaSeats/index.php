<?php
require_once("./support/_components.php");
require_once("./support/_database.php");

startPage("Proiezioni",0);

drawLogo();
drawUserbar(0);

connect($dbcon);

$DAY_INTERVAL = 15;

$query ="select codiceFilm,titolo,descrizione, urlLocandina,TIME_FORMAT(durata,'%k:%i')
from Film join Proiezioni on (codiceFilm=film)
where data >= current_date() and data < current_date() + interval 15 day
group by codiceFilm,titolo,descrizione, urlLocandina,durata";


$films=mysql_query($query) or die("Errore");

if (mysql_num_rows($films) == 0){
	drawMsg("warning","Non c'e' nessuno spettacolo in programma per i prossimi $DAY_INTERVAL giorni.");
}

while ($row = mysql_fetch_row($films)){
	
	$codiceFilm=$row[0];


	$query="select distinct DATE_FORMAT(data,'%e/%c/%Y'), TIME_FORMAT(ora,'%k:%i') 
			from Proiezioni
			where film = $codiceFilm and
			data >= current_date() and data < current_date() + interval 15 day
			order by data, ora";
	
	echo "<hr />";
	
	$proiezioniFilm =mysql_query($query);
	while ($proiezione = mysql_fetch_row($proiezioniFilm)){
		$data = $proiezione[0];
		$ora = $proiezione[1];
		if (!isset($proiezioni[$data]))$proiezioni[$data] = ""; //per sopprimere il NOTICE 
		$proiezioni[$data] = $proiezioni[$data]."$ora "; 
	}

	$row[]=$proiezioni;
	$proiezioni=array();
	drawFilm($row);

}


endPage();
?>
