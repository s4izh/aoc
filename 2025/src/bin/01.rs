static DAY_STR: &str = "01";

fn part1(file_contents: &str) -> u32 {
    let lines = file_contents.lines();
    let mut pos: i32 = 50;
    let mut count: u32 = 0;
    for line in lines {
        if line.is_empty() {
            continue;
        }
        let (dir_str, num_str) = line.split_at(1);
        let num: i32 = num_str.parse().unwrap();
        if dir_str == "R" {
            pos += num;
        } else if dir_str == "L" {
            pos -= num;
        }
        pos = pos.rem_euclid(100);
        if pos == 0 {
            count += 1;
        }
    }
    count
}

fn part1_func(file_contents: &str) -> u32 {
    let lines = file_contents.lines().filter(|line| !line.is_empty());
    let (_, count) = lines
        .map(|line| {
            let (dir_str, num_str) = line.split_at(1);
            let step: i32 = num_str.parse().unwrap();
            if dir_str == "R" { step } else { -step }
        })
        .fold((50, 0), |(pos, total_count), current_steps| {
            let current = pos + current_steps;
            let count = if (current % 100) == 0 { 1 } else { 0 };
            (current.rem_euclid(100), total_count + count)
        });
    count
}

fn part2(file_contents: &str) -> u32 {
    let lines = file_contents.lines();
    let mut pos: i32 = 50;
    let mut count: u32 = 0;
    for line in lines {
        if line.is_empty() {
            continue;
        }
        let (dir_str, num_str) = line.split_at(1);
        let num: i32 = num_str.parse().unwrap();

        let ticks_to_next_zero = if dir_str == "R" {
            100 - pos
        } else {
            if pos == 0 { 100 } else { pos }
        };

        if num >= ticks_to_next_zero {
            count += 1 + ((num - ticks_to_next_zero) / 100) as u32;
        };

        if dir_str == "R" {
            pos += num;
        } else {
            pos -= num;
        }

        pos = pos.rem_euclid(100);
    }
    count
}

fn part2_func(file_contents: &str) -> u32 {
    let lines = file_contents.lines().filter(|line| !line.is_empty());
    let (_, count) = lines
        .map(|line| {
            let (dir_str, num_str) = line.split_at(1);
            let step: i32 = num_str.parse().unwrap();
            if dir_str == "R" { step } else { -step }
        })
        // first parameter of the lambda is the fold "state"
        // second parameter is the iterator value at current position
        .fold((50, 0), |(pos, total_count), current_steps| {
            let ticks_to_next_zero = if current_steps > 0 {
                100 - pos
            } else {
                if pos == 0 { 100 } else { pos }
            };

            let hits = if current_steps.abs() >= ticks_to_next_zero {
                1 + (current_steps.abs() - ticks_to_next_zero) / 100
            } else {
                0
            };

            let next_pos = (pos + current_steps).rem_euclid(100);
            (next_pos, total_count + hits)
        });
    count as u32
}

fn main() {
    println!("Hello, world!");
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn part1_base() {
        let contents =
            std::fs::read_to_string(format!("inputs/{DAY_STR}/base.txt")).unwrap();
        assert_eq!(part1(&contents), 3);
    }
    #[test]
    fn part1_full() {
        let contents =
            std::fs::read_to_string(format!("inputs/{DAY_STR}/full.txt")).unwrap();
        assert_eq!(part1(&contents), 989);
    }

    #[test]
    fn part1_func_base() {
        let contents =
            std::fs::read_to_string(format!("inputs/{DAY_STR}/base.txt")).unwrap();
        assert_eq!(part1_func(&contents), 3);
    }
    #[test]
    fn part1_func_full() {
        let contents =
            std::fs::read_to_string(format!("inputs/{DAY_STR}/full.txt")).unwrap();
        assert_eq!(part1_func(&contents), 989);
    }

    #[test]
    fn part2_base() {
        let contents =
            std::fs::read_to_string(format!("inputs/{DAY_STR}/base.txt")).unwrap();
        assert_eq!(part2(&contents), 6);
    }
    #[test]
    fn part2_full() {
        let contents =
            std::fs::read_to_string(format!("inputs/{DAY_STR}/full.txt")).unwrap();
        assert_eq!(part2(&contents), 5941);
    }

    #[test]
    fn part2_func_base() {
        let contents =
            std::fs::read_to_string(format!("inputs/{DAY_STR}/base.txt")).unwrap();
        assert_eq!(part2_func(&contents), 6);
    }
    #[test]
    fn part2_func_full() {
        let contents =
            std::fs::read_to_string(format!("inputs/{DAY_STR}/full.txt")).unwrap();
        assert_eq!(part2_func(&contents), 5941);
    }
}
