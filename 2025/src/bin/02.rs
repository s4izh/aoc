static DAY_STR: &str = "02";

#[derive(Debug)]
struct IdPair {
    start: u64,
    end: u64,
}

use std::str::FromStr;

impl FromStr for IdPair {
    type Err = String;

    fn from_str(s: &str) -> Result<Self, Self::Err> {
        let (left, right) = s
            .trim()
            .split_once('-')
            .ok_or_else(|| format!("Input '{}' does not contain a dash", s))?;

        let start = left.trim().parse::<u64>().map_err(|_| "Bad start")?;
        let end = right.trim().parse::<u64>().map_err(|_| "Bad end")?;

        Ok(IdPair { start, end })
    }
}

impl IdPair {
    fn sum_of_invalid_ids_in_range(&self) -> u64 {
        let mut sum = 0;
        for n in self.start..=self.end {
            let mut m = n;
            let mut digit_count = 0;
            while m >= 10 {
                m = m / 10;
                digit_count += 1;
            }
            digit_count += 1;

            if digit_count % 2 != 0 {
                continue;
            }

            let half = digit_count / 2;

            let divisor = 10u32.pow(half) as u64;

            let left = n / divisor;
            let right = n % divisor;

            if left == right {
                println!("bad ID: {n}");
                sum += n;
            }
        }
        sum
    }
}

fn is_id_invalid_part1(id: u64) -> bool {
    let s = id.to_string();
    let len = s.len();

    if len % 2 != 0 {
        return false;
    }

    let half = len / 2;

    if &s[0..half] == &s[half..] {
        true
    } else {
        false
    }
}

fn is_id_invalid_part2(id: u64) -> bool {
    let s = id.to_string();
    // A string is made of a repeated sequence if and only if it is 
    // found within itself doubled, excluding the start and end positions.
    let ss = format!("{}{}", s, s);
    ss[1..ss.len() - 1].contains(&s)
}

fn part1_old(file_contents: &str) -> u64 {
    file_contents
        .split(",")
        .filter_map(|p| p.parse::<IdPair>().ok())
        .map(|p| p.sum_of_invalid_ids_in_range())
        .sum::<u64>()
}

fn solve(file_contents: &str, check_fn: fn(u64) -> bool) -> u64 {
    file_contents
        .split(",")
        .filter_map(|p| p.trim().parse::<IdPair>().ok())
        .map(|p| {
            (p.start..=p.end)
                .filter(|&id| check_fn(id))
                .sum::<u64>()
        })
        .sum()
}

fn part1(file_contents: &str) -> u64 {
    solve(file_contents, is_id_invalid_part1)
}

fn part2(file_contents: &str) -> u64 {
    solve(file_contents, is_id_invalid_part2)
}

fn main() {
    println!("Hello, world!");
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn part1_base() {
        let contents = std::fs::read_to_string(format!("inputs/{DAY_STR}/base.txt")).unwrap();
        assert_eq!(part1(&contents), 1227775554);
    }

    #[test]
    fn part1_full() {
        let contents = std::fs::read_to_string(format!("inputs/{DAY_STR}/full.txt")).unwrap();
        assert_eq!(part1(&contents), 21898734247);
    }

    #[test]
    fn part2_base() {
        let contents = std::fs::read_to_string(format!("inputs/{DAY_STR}/base.txt")).unwrap();
        assert_eq!(part2(&contents), 4174379265);
    }
    #[test]
    fn part2_full() {
        let contents = std::fs::read_to_string(format!("inputs/{DAY_STR}/full.txt")).unwrap();
        assert_eq!(part2(&contents), 28915664389);
    }
}
