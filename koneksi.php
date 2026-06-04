<?php
$host = "localhost";
$user = "root";
$pass = "";
$db = "parking_gate";

$conn = mysqli_connect($host, $user, $pass, $db);

if (!$conn) {
    die("Koneksi gagal");
}
?>