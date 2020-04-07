import java.util.*
import java.io.*

fun main(args : Array<String>){
    val br = BufferedReader(InputStreamReader(System.`in`))
    val N = br.readLine()!!.toInt()
    val M = br.readLine()!!.toInt()
    var adj : MutableList<MutableList<Pair<Int, Int>>> = mutableListOf()
    for (i in 0..N)  adj.add(mutableListOf())
    for (i in 0..(M - 1)){
        val (u, v, w) = br.readLine()!!.trim().split(' ').map{ it.toInt() }
        adj[u].add(Pair<Int, Int>(v, w))
    }
    val (S, E) = br.readLine()!!.trim().split(' ').map{ it.toInt() }
    var vis = IntArray(N + 1) { 0 }
    var dist = IntArray(N + 1) { 1e9.toInt() }
    var pq = PriorityQueue<Pair<Int, Int>>(kotlin.Comparator { o1, o2 ->  o1.first.compareTo(o2.first)})
    pq.add(Pair<Int, Int>(0, S))
    dist[S] = 0
    while(!pq.isEmpty()){
        var cur : Int = 0
        do{
            cur = pq.remove().second
        }while(!pq.isEmpty() && vis[cur] == 1)
        if(vis[cur] == 1)   break
        vis[cur] = 1
        for(i in adj[cur]){
            val next = i.first
            val ndist = i.second
            if(dist[next] > dist[cur] + ndist){
                dist[next] = dist[cur] + ndist
                pq.add(Pair<Int, Int>(dist[next], next))
            }
        }
    }
    println(dist[E])
}