<?php
require_once('./support/_database.php');

function login($username, $password){
	if(session_id() == '') 
		session_start();
	connect($dbcon);
	$password = sha1($password);
	$query = "select * from Utenti natural left join Staff natural left join Clienti where username=\"$username\" and password=\"$password\"";
	

	$result = mysql_query($query);
	$row= mysql_fetch_row($result);
	
	if (mysql_num_rows($result)==1){
		if (isset($row[5])){ //EMAIL
			$_SESSION["email"]=$row[5];
			$_SESSION["username"]=$row[0];
			$_SESSION["auth_level"]=1;
		} else{
			$_SESSION["username"]=$row[0];
			if ($row[4]=="Commesso")
				$_SESSION["auth_level"]=2;
			else
				$_SESSION["auth_level"]=3;
		}
		$_SESSION["SUCCESS_MSG"][]="Benvenuto ".$_SESSION["username"]."!";
		header("location: index.php");
		return true;
	}
	else{
		$_SESSION["ERROR_MSG"][] = "Nome utente o password errati!";
		//header("location: login.php");
		return false;
	}
	
}


function logout(){
	if(session_id() == '')
		session_start();
	$_SESSION = array();
	if (ini_get("session.use_cookies")) {
	    $params = session_get_cookie_params();
	    setcookie(session_name(), '', time() - 42000,
	        $params["path"], $params["domain"],
	        $params["secure"], $params["httponly"]
	    );
	}
	session_destroy();
}

function verifyAuth($auth){
	if (!isset($_SESSION["auth_level"])) $_SESSION["auth_level"] =0; //per sopprimere il notice
	if ($_SESSION["auth_level"] < $auth){
		$_SESSION["ERROR_MSG"][] = "Permesso negato!";
		//header("location:javascript://history.go(-1)");
		$url = baseUrl()."/login.php";
		header("location: $url"); //il redirect non è istantaneo, devo quindi comunicare a chi ha chiamato la funzione che l'utente non è autorizzato.
		return false; 
	}
	return true;
}

function baseUrl() {
 return "http://{$_SERVER['HTTP_HOST']}". dirname($_SERVER['PHP_SELF']);
}

function sendRecapMail($codicePrenotazione){
	//Si assume che ci sia un utente loggato.
	if ($_SESSION["email"]!=""){
		$email=$_SESSION["email"];
		$oggetto = "Riepilogo prenotazione [$codicePrenotazione]";

		connect($db);
		$query = "	select DATE_FORMAT(p.data,'%e/%c/%Y'), DATE_FORMAT(pp.data,'%e/%c/%Y'), TIME_FORMAT(pp.ora,'%k:%i'), f.titolo, count(*), costoTotalePrenotazione($codicePrenotazione) 
					from Prenotazioni p natural join PostiPrenotati
						join Proiezioni pp on (p.proiezione = pp.codiceProiezione)
						join Film f on (pp.film = f.codiceFilm)
					where codicePrenotazione = $codicePrenotazione
					group by codicePrenotazione, p.data, pp.data, pp.ora, f.titolo";
		
		$result=mysql_query($query);
		$row = mysql_fetch_row($result);
		$dataPrenotazione = $row[0];
		$dataSpettacolo = $row[1];
		$oraSpettacolo = $row[2];
		$film = $row[3];
		$numPosti = $row[4];
		$costo = $row[5];

		$corpoMail = "	Ciao ".$_SESSION["username"].", \r\n
						ecco a lei il riepilogo della sua prenotazione effettuata\r\n in data $dataPrenotazione:\r\n
						Film: $film\r\n
						Data: $dataSpettacolo $oraSpettacolo \r\n
						Numero posti: $numPosti\r\n
						Costo Totale: $costo Euro\r\n\r\n
						Le ricordiamo che la prenotazione deve essere ritirata almeno\r\n 15 minuti prima dell'inizio dello spettacolo.\r\n
						Per maggiori informazioni visiti il nostro sito.";

		$sent = mail($email,$oggetto,$corpoMail);/**/

		if (!$sent)
			$_SESSION["ERROR_MSG"][] ="Si è verificato un errore nell'invio della mail, la prenotazione è stata comunque effettuata.";
	}
}

function isTime($time,$seconds=false) {
    $pattern = "/^"."([1-2][0-3]|[01]?[1-9])".":([0-5]?[0-9])".($seconds ? ":([0-5]?[0-9])" : "")."$/";
    if (preg_match($pattern, $time)) {
        return true;
    }
    return false;
}

?>
