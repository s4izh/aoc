use std::fs::File;
use std::io::{self, prelude::*, BufReader};
use std::num::ParseIntError;
use std::str::FromStr;

#[derive(Debug)]
struct Mapping {
    destination: u64,
    source: u64,
    range: u64,
}

impl FromStr for Mapping {
    type Err = ParseIntError;

    fn from_str(s: &str) -> Result<Self, Self::Err> {
        let parts: Vec<&str> = s.split_whitespace().collect();
        if parts.len() != 3 {
            return Err("Invalid format".parse::<u64>().unwrap_err());
        }
        let destination = parts[0].parse::<u64>()?;
        let source = parts[1].parse::<u64>()?;
        let range = parts[2].parse::<u64>()?;

        Ok(Mapping {
            destination,
            source,
            range,
        })
    }
}

pub fn add(left: usize, right: usize) -> usize {
    left + right
}

fn get_location(seed: u64, mappings: &Vec<Vec<Mapping>>) -> u64 {
    let mut value = seed;

    for map in mappings.iter() {
        value = map
            .iter()
            .find(|mapping| value >= mapping.source && value < mapping.source + mapping.range)
            .map_or(value, |mapping| {
                let offset = value - mapping.source;
                mapping.destination + offset
            });
    }

    value
}

fn part1(filename: &str) -> io::Result<u64> {
    let file = File::open(filename)?;
    let reader = BufReader::new(file);

    let mut seeds: Vec<u64> = Vec::new();
    let mut maps: Vec<Vec<Mapping>> = Vec::new();
    let mut min_location = u64::MAX;

    for line in reader.lines() {
        let line = line?;
        if line.is_empty() {
            continue;
        }
        if line.contains("seeds") {
            seeds = line
                .split(":")
                .nth(1)
                .expect("expected seeds to have seeds")
                .split(" ")
                .filter(|s| !s.is_empty())
                .map(|s| s.parse::<u64>().unwrap())
                .collect();
        } else if line.contains("map") {
            let stripped = line.trim().split(" ").nth(0).unwrap();
            println!("{}", stripped);
            maps.push(Vec::new());
        } else {
            if let Some(map) = maps.last_mut() {
                map.push(Mapping::from_str(&line).unwrap());
            }
        }
    }

    for seed in seeds.into_iter() {
        let location = get_location(seed, &maps);

        if location <= min_location {
            min_location = location;
        }
    }

    Ok(min_location)
}

fn main() {
    let _ = part1("input/mini_input.txt");

    println!("Hello, world!");
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn part1_test_mini() {
        assert_eq!(part1("input/mini_input.txt").unwrap(), 35);
    }

    #[test]
    fn part1_test_big() {
        assert_eq!(part1("input/full_input.txt").unwrap(), 836040384);
    }

    #[test]
    fn part2_test_mini() {
        let result = add(2, 2);
        assert_eq!(result, 4);
    }

    #[test]
    fn part2_test_big() {
        let result = add(2, 2);
        assert_eq!(result, 4);
    }
}
