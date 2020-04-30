import java.util.*
import kotlin.collections.ArrayList

class MCMF {
    private var graph: ArrayList<ArrayList<Edge>>
    private var prevNode: Array<Int>
    private var prevNodeIndex: Array<Int>
    private var vertexCount: Int = 0

    var source: Int = 0
    var sink: Int = 0

    constructor(vertexCount: Int){
        this.vertexCount = vertexCount
        graph = ArrayList<ArrayList<Edge>>(vertexCount + 2)
        prevNode = Array<Int>(vertexCount + 2, { it -> 0 })
        prevNodeIndex = Array<Int>(vertexCount + 2, { it -> 0})
        for (i in 0 until vertexCount + 2) {
            graph.add(arrayListOf(Edge(0, 0, 0, 0)))
        }
        source = 0
        sink = vertexCount + 1
    }

    fun addEdge(current: Int, next: Int, capacity: Int, cost: Int) {
        graph[current].add(Edge(next, capacity, cost, graph[next].size))
        graph[next].add(Edge(current, 0, -cost, graph[current].size - 1))
    }

    private fun shortestPathFasterAlgorithm(): Boolean {
        var dist = Array<Int>(vertexCount + 2, {it -> Int.MAX_VALUE})
        var inQ = Array<Int>(vertexCount + 2, { it -> 0 })

        var q: Queue<Int> = LinkedList()
        q.add(source)
        inQ[source] = 1
        dist[source] = 0

        while (!q.isEmpty()) {
            var current = q.poll()
            inQ[current] = 0
            for (i in 0 until graph[current].size){
                val next = graph[current][i].vertex!!
                val capacity = graph[current][i].capacity!!
                val nextCost = graph[current][i].cost!!
                if (capacity != 0 && dist[next] > dist[current] + nextCost) {
                    dist[next] = dist[current] + nextCost
                    prevNode[next] = current
                    prevNodeIndex[next] = i
                    if (inQ[next] == 0){
                        q.add(next)
                        inQ[next] = 1
                    }
                }
            }
        }
        return dist[sink] != Int.MAX_VALUE
    }

    fun match(): Int {
        var totalFlow = 0
        var totalCost = 0
        while(shortestPathFasterAlgorithm()) {
            var maxFlow = Int.MAX_VALUE
            var current = sink
            while (current != source) {
                maxFlow = kotlin.math.min(maxFlow, graph[prevNode[current]][prevNodeIndex[current]].capacity!!)
                current = prevNode[current]
            }
            current = sink
            while (current != source) {
                graph[prevNode[current]][prevNodeIndex[current]].capacity =
                        graph[prevNode[current]][prevNodeIndex[current]].capacity!! - maxFlow
                graph[current][graph[prevNode[current]][prevNodeIndex[current]].reversedEdge!!].capacity =
                        graph[current][graph[prevNode[current]][prevNodeIndex[current]].reversedEdge!!].capacity!! + maxFlow
                totalCost += maxFlow * graph[prevNode[current]][prevNodeIndex[current]].cost!!
                current = prevNode[current]
            }
            totalFlow += maxFlow
        }
        return totalCost
    }

    private inner class Edge {
        var vertex: Int? = null
        var capacity: Int? = null
        var cost: Int? = null
        var reversedEdge: Int? = null

        constructor(vertex: Int?, capacity: Int?, cost: Int?, reversedEdge: Int?) {
            this.vertex = vertex
            this.capacity = capacity
            this.cost = cost
            this. reversedEdge = reversedEdge
        }
    }

}