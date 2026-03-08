<h2 style= "text-align: center;"> Tarea 1 de Matematicas Discretas </h2>
<br>
<b> En esta tarea se implemento de manera profunda el algoritmo de dijkstra, se hizo de 2 maneras distintas: </b>
<br>
<h3> Primera forma -- Senderos_de_LuzV1 --</h3>
<p> En esta primera implementacion se uso listas para generar las adyacencias al vertice escogido como el menor para luego recorrer esta misma lista y buscar los adyacentes menores que cumplan con las propiedades del problema, posteriormente a esto se añaden 
a la lista de solution, donde tendremos solo los vertices ya elegidos en la solucion final y marcados por el Dijkstra. </p>
<br>
<p> El problema de esta implementacion, que aunque funciona a la perfeccion, es demasiado especifica, como dicen por ahi es como matar a una mosca con un tanque, guarda perfectamente la informacion de cada vertice y mantiene mucha informacion que suele ser
importante para problemas relacionados a la IA, el tema es que no tiene una complejidad temporal tan eficiente como su contraparte v2, ya que esta version no cuenta con relajacion de vertices, teniendo en la lista de adyacencias multiples repetidos para luego
ser elegidos posteriormente y eliminar todos esos repetidos. El tema es que aunque sea Dijkstra y funcione perfectamente, no es la mejor solucion y no es fiel a los principios matematicos que describe el algoritmo de dijkstra, pero es una solucion igualmente valida</p>
<h3> Segunda forma -- Senderos_de_LuzV2 --</h3>
<p> En esta segunda forma se mejora de manera significativa la complejidad temporal de este algoritmo, puesto que la busqueda de dichos vertices para ser marcados por el algoritmo es O(V^2) donde V representa la cantidad de vertices. En cambio en el anterior teniamos
una lista que se expandia y contraia en cualquier momento y no garantizaba una complejidad temporal menor a O(V^2). El mayore punto fuerte de esta version es la conocida relajacion de vertices, permitiendo actualizar la distancia y el recorrido con el arreglo parent sin
necesidad de añadir un nuevo vertice.</p>
<br>
<p> Esta basado ademas de una forma un poco mas estricta en el algoritmo de dijkstra presentado en el libro de matematicas discretas ROSEN.</p>
<br>
<p> Para ver mas informacion sobre el enunciado de la tarea, abrir el pdf relacionado a la misma en el repositorio </p>

