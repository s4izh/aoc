use std::fs;

const FULL_INPUT: &str = "input/full_input.txt";
const MINI_INPUT: &str = "input/part1_input.txt";

const GAME_RULES: [(&str, usize); 3] = [("red", 12), ("green", 13), ("blue", 14)];

fn max_appearances(draws: &str, color: &str) -> usize {
    draws
        .split("; ")
        .flat_map(|draw| {
            draw.split(", ").map(|count| {
                let (n, c) = count.split_once(' ').expect("count");
                (c == color)
                    .then(|| n.parse().expect("usize count"))
                    .unwrap_or(0)
            })
        })
        .max()
        .expect("counts")
}

fn part1(file_path: &str) -> usize {
    let binding = fs::read_to_string(file_path).expect("Error reading file");
    let mut lines = binding.split('\n').collect::<Vec<&str>>();

    let index = lines.len() - 1;
    if lines[index].is_empty() {
        lines.remove(index);
    }

    lines.iter().fold(0, |acc, line| {
        let (game_id, draws) = line.split_once(": ").expect("first split");
        acc + GAME_RULES
            .into_iter()
            .all(|(color, n)| max_appearances(draws, color) <= n)
            .then(|| {
                game_id
                    .trim_start_matches("Game ")
                    .parse()
                    .expect("expected game id")
            })
            .unwrap_or(0)
    })
}

fn part2(file_path: &str) -> usize {
    let binding = fs::read_to_string(file_path).expect("Error reading file");
    let mut lines = binding.split('\n').collect::<Vec<&str>>();

    let index = lines.len() - 1;
    if lines[index].is_empty() {
        lines.remove(index);
    }

    lines.iter().fold(0, |acc, line| {
        let (game_id, draws) = line.split_once(": ").expect("first split");
        acc + GAME_RULES
            .into_iter()
            .all(|(color, n)| max_appearances(draws, color) <= n)
            .then(|| {
                game_id
                    .trim_start_matches("Game ")
                    .parse()
                    .expect("expected game id")
            })
            .unwrap_or(0)
    })
}

fn main() {
    println!("part1: {}", part1(MINI_INPUT));
    println!("part1: {}", part1(FULL_INPUT));
    println!("part2: {}", part2(MINI_INPUT));
    println!("part2: {}", part2(FULL_INPUT));
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn part1_test() {
        assert_eq!(part1(MINI_INPUT), 8);
        assert_eq!(part1(FULL_INPUT), 2406);
    }

    #[test]
    fn part2_test() {
        assert_eq!(part2(MINI_INPUT), 8);
        assert_eq!(part2(FULL_INPUT), 2406);
    }
}
