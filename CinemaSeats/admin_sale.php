<?php

require_once('./support/_components.php');
require_once('./support/_database.php');
require_once('./support/_various.php');

$autorizzato =startPage("Amministrazione - Sale",3);


if ($autorizzato){
	connect($dbcon);

	if ($_POST["action"]=="insert"){

		$nomeSala = trim($_POST["nomeSala"]);
		$numeroFile = $_POST["numeroFile"];
		$numeroPosti = $_POST["numeroPosti"];
		$err =false;

		if ($nomeSala==""){
			$_SESSION["ERROR_MSG"][] = "Il nome della sala non puo' essere vuoto";
			$err=true;
		}
		if (!is_numeric($numeroFile) || $numeroFile <=0){
			$_SESSION["ERROR_MSG"][] = "Numero file non valido";
			$err=true;
		}
		if (!is_numeric($numeroPosti) || $numeroPosti <=0){
			$_SESSION["ERROR_MSG"][] = "Numero posti non valido";
			$err=true;
		}
		if (!$err){
			$query="insert into Sale values (0,'$nomeSala')";
			if (mysql_query($query)){
				$idSala=mysql_insert_id();
				$query="";
				for ($i=0; $i < $numeroFile; $i++) { 
					for ($j=1; $j <= $numeroPosti ; $j++) { 
						$fila=chr(65+$i);
						$query=" insert into Posti values(0,'$fila',$j,$idSala);";
						mysql_query($query);
					}
				}
				$_SESSION["SUCCESS_MSG"][] ="Inserimento completato";
				$_POST=array();
			}
			else{
				$_SESSION["ERROR_MSG"][] ="Esiste già una sala con lo stesso nome";
			}
		}	
	}
	if ($_POST["action"]=="delete"){
		$id = $_POST["codiceSala"]*1;
		$query = "delete from Sale where codiceSala=$id";

		mysql_query($query);
		$_SESSION["SUCCESS_MSG"][] ="Sala cancellata";
	}



	drawLogo();

	drawUserBar(4);
	drawAdminBar(4);

	echo '<div class="row">';
	echo '<div class="col-md-4">';
	echo '<h3>Sale presenti</h3>';


	$query="select nome, count(*),codiceSala from Sale join Posti on (codiceSala=sala) group by codiceSala, nome";


	$result = mysql_query($query);
	drawStartTable(array("Nome","Posti","Azioni"));

	while ($row = mysql_fetch_row($result)){
		$js="return confirm('Cancellando una sala cancellerai tutti i posti presenti, inoltre verrano cancellate anche tutte gli spettacoli e le proiezioni legate alla sala che stai per cancellare. Sei sicuro di voler proseguire?');";
		$formPerCancellazione ='<form method="POST" action = "'.baseUrl().'/admin_sale.php">
								<input type="submit" value="Cancella" onClick="'.$js.'" value="Cancella" class="btn btn-danger btn-xs">
								<input type="hidden" name ="action" value="delete"/>
								<input type="hidden" name ="codiceSala" value="'.$row[2].'"/>
								</form>';
		drawTableRow(array($row[0],$row[1],$formPerCancellazione));
	}

	drawEndTable();


	echo '</div>'; //Fine prima colonna

	echo '<div class="col-md-8">';
	echo '<h3>Inserisci</h3>';


	drawStartForm("/admin_sale.php","form-horizontal");

	drawFormField("text","nomeSala","Nome sala",$_POST["nomeSala"]);
	drawFormField("number","numeroFile","Numero file",$_POST["numeroFile"],"min=\"1\" max=\"26\"");
	drawFormField("number","numeroPosti","Numero posti per fila",$_POST["numeroPosti"]);

	drawFormField("submit","","","Inserisci","btn btn-default");

	drawHiddenField("action","insert");

	echo '</div>';
}
endPage();

?>