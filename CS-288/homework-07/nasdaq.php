<html>

<head>
    <title>Nasdaq Data</title>
</head>

<body>
    <table align="center" border="1">

        <?php
        
        // sorting is handled based on query string params
        $queryString = $_GET ? $_SERVER['QUERY_STRING'] : 'DEFAULT';

        // log the query string to the console
        echo '<script> console.log("'.$queryString.'") </script>';

        echo '<tr class="header" style="text-align: center;">';
        echo '<td>exchange</td>';
        
        if ($queryString == 'orderBy=symbol&sort=ASC') {
            echo '<td><a href="?orderBy=symbol&sort=DESC">symbol</a></td>';
        } else {
            echo '<td><a href="?orderBy=symbol&sort=ASC">symbol</a></td>';
        }
        
        if ($queryString == 'orderBy=company&sort=ASC') {
            echo '<td><a href="?orderBy=company&sort=DESC">company</a></td>';
        } else {
            echo '<td><a href="?orderBy=company&sort=ASC">company</a></td>';
        }

        if ($queryString == 'orderBy=volume&sort=ASC') {
            echo '<td><a href="?orderBy=volume&sort=DESC">volume</a></td>';
        } else {
            echo '<td><a href="?orderBy=volume&sort=ASC">volume</a></td>';
        }

        if ($queryString == 'orderBy=price&sort=ASC') {
            echo '<td><a href="?orderBy=price&sort=DESC">price</a></td>';
        } else {
            echo '<td><a href="?orderBy=price&sort=ASC">price</a></td>';
        }

        if ($queryString == 'orderBy=percentChange&sort=ASC') {
            echo '<td><a href="?orderBy=percentChange&sort=DESC">change</a></td>';
        } else {
            echo '<td><a href="?orderBy=percentChange&sort=ASC">change</a></td>';
        }

        echo '</tr>';

        $cnx = new mysqli('localhost', 'USERNAME', 'PASSWORD', 'DATABASE');

        if ($cnx->connect_error) {
            die('Connection failed: ' . $cnx->connect_error);
        }

        // default sort by symbol
        $validCols = array('symbol', 'company', 'volume', 'price', 'percentChange');
        $orderBy = isset($_GET['orderBy']) && in_array($_GET['orderBy'], $validCols) ? $_GET['orderBy'] : 'symbol';

        // default sort ASC
        $sortyBy = (isset($_GET['sort']) && $_GET['sort'] == 'ASC' || $_GET['sort'] == 'DESC') ? $_GET['sort'] : 'ASC';

        $query = $queryString == 'DEFAULT' ? "SELECT * FROM nasdaq" : "SELECT * FROM nasdaq ORDER BY $orderBy $sortyBy"; 
        $cursor = $cnx->query($query);

        while ($row = $cursor->fetch_assoc()) {
            echo '<tr>';
            echo '<td>' . $row['exchange'] . '</td><td>' . $row['symbol'] . '</td><td>' . $row['company'] . '</td><td align="right">' . $row['volume'] . '</td><td align="right">' . $row['price'] .'</td><td align="right">' . $row['percentChange'] .'</td>';
            echo '</tr>';
        }

        $cnx->close();
        ?>

    </table>
      
    <!-- some css to make the table look nicer -->
    <style>
       * {
        padding: 0;
        margin: 0;
        font-size: 1.2rem;
      }

      body {
        background: #4a4a48;
      }

      a,
      a:link,
      a:visited,
      a:hover,
      a:active {
        color: #000;
        text-decoration: none;
      }

      .header {
        background: #4a4a48 !important;
      }

      .header td, .header td a {
        font-weight: bold;
        color: #fff;
      }

      table {
        border-collapse: collapse;
        overflow: hidden;
        width: 100%;
      }

      td {
        border: 1px solid #ddd;
        padding: 0.5rem;
      }

      tr:nth-child(even) {
        background: #fff;
      }

      tr:nth-child(odd) {
        background: #f2f2f2;
      }
    </style>
</body>

</html>
