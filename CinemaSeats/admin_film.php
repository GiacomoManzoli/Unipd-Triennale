<?php
require_once('./support/_components.php');
require_once('./support/_various.php');
require_once('./support/_database.php');

$autorizzato = startPage("Amministrazione - Film",3);



if ($autorizzato){
	connect($dbcon);

	if ($_POST["action"]=="insert"){
		$titolo = trim($_POST["titolo"]);
		$descrizione = trim($_POST["desc"]);
		$urlLocandina = trim($_POST["urlLocandina"]);
		$durata = $_POST["durata"];
		$err=false;

		if ($titolo==""){
			$_SESSION["ERROR_MSG"][] ="Il titolo non puo' essere vuoto";
			$err=true;
		}
		if ($durata==0){
			$_SESSION["ERROR_MSG"][] ="La durata non puo' essere 0";
			$err=true;
		}
		if (!$err){
			if ($urlLocandina!=""){
				$query ="insert into Film values(0,'$titolo','$descrizione','$urlLocandina','$durata')";
			}
			else{
				$query ="insert into Film(codiceFilm,titolo,descrizione,durata) values(0,'$titolo','$descrizione','$durata')";

			}
			mysql_query($query);
			$_SESSION["SUCCESS_MSG"][] ="Inserimento completato";
			$_POST=array();
		}

	}
	if ($_POST["action"]=="delete"){
		$id = $_POST["codiceFilm"]*1;
		$query = "delete from Film where codiceFilm=$id";

		mysql_query($query);
		if (mysql_error()==""){
			$_SESSION["SUCCESS_MSG"][] ="Film cancellato";
		}else{
			$_SESSION["ERROR_MSG"][] ="Non e' stato possibile cancellare il film";
		}
	}


	drawLogo();
	drawUserBar(4);
	drawAdminBar(3);

	echo '<div class="row">';
	echo '<div class="col-md-12">';
	echo '<h3>Inserisci Film</h3>';

	drawStartForm("/admin_film.php","form-horizontal");

	drawFormField("text","titolo","Titolo",$_POST["titolo"]);
	drawFormField("text","desc","Descrizione",$_POST["desc"]);
	drawFormField("time","durata","Durata",$_POST["durata"]);
	drawFormField("url","urlLocandina","URL Locandina",$_POST["urlLocandina"]);

	echo '<div class="form-group">';
	echo '<div class="col-sm-offset-2 col-sm-10"><input type="submit" class="btn btn-default" value="Inserisci"/></div>';
	echo '</div>';
	drawHiddenField("action","insert");

	drawEndForm();

	echo '</div>';
	echo '</div>'; #fine row

	echo '<div class="row">';
	echo '<div class="col-md-12">';
	echo '<h3>Lista film</h3>';

	$query = "select codiceFilm, titolo, TIME_FORMAT(durata,'%k:%i'), descrizione, urlLocandina from Film";
	$result = mysql_query($query);
	drawStartTable(array("Codice","Titolo","Durata","Descrizione","URL Locandina","Azioni"));
	while ($row=mysql_fetch_row($result)){
		$js="return confirm('Cancellando un film cancellerai anche le proiezioni e le prenotazioni che lo riguardano, sei sicuro di voler continuare?');";
		
		$formCancella ='<form method="POST" action = "'.baseUrl().'/admin_film.php">
						<input type="submit" valure="Cancella" onClick="'.$js.'" value="Cancella" class="btn btn-danger btn-xs">
						<input type="hidden" name ="action" value="delete"/>
						<input type="hidden" name ="codiceFilm" value="'.$row[0].'"/>
						</form>';
		drawTableRow(array($row[0],$row[1],$row[2],$row[3],$row[4],$formCancella));
	}
	drawEndTable();

	echo '</div>';
	echo '</div>';#fine row


}

endPage();
?>