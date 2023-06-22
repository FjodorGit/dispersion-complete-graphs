#![feature(let_chains)]

use rand::{self, distributions::Uniform, thread_rng, Rng};

const N: usize = 100_000;
const M: usize = 50_000;

//implementation with graph represented by vector
fn step(graph: &mut Vec<usize>, distribution: &Uniform<usize>) {
    let mut destinations: Vec<usize> = vec![];
    for index in 0..N {
        match graph[index] {
            0 => continue,
            1 => destinations.push(index),
            _ => {
                let mut sample_destinations: Vec<usize> = thread_rng()
                    .sample_iter(distribution)
                    .take(graph[index])
                    .collect();
                destinations.append(&mut sample_destinations)
            }
        }
    }
    *graph = vec![0; N];
    for destination in destinations.iter() {
        graph[*destination] += 1
    }
}

fn main() {
    let mut graph = vec![0; N];
    graph[0] = M;
    let distribution_over_nodes = Uniform::from(0..N);
    let mut steps = 0;
    while let Some(max) = graph.iter().max() && *max > 1 {
        steps += 1;
        step(&mut graph, &distribution_over_nodes);
        assert!(graph.clone().iter().sum::<usize>() == M);
        println!("Steps: {:?}", steps);
        // println!("{:?} \n", graph);
    }
}
