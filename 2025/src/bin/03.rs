static DAY_STR: &str = "03";

fn part1(file_contents: &str) -> u64 {
    file_contents
        .lines()
        .filter(|line| !line.is_empty())
        .map(|bank| {
            // Convert the string of characters into a list of digits
            let digits: Vec<u32> = bank.chars().filter_map(|c| c.to_digit(10)).collect();

            if digits.len() < 2 {
                return 0;
            }

            let mut max_ones_digit = 0;
            let mut best_joltage = 0;

            for i in (1..digits.len()).rev() {
                max_ones_digit = max_ones_digit.max(digits[i]);

                let tens = digits[i - 1];
                let current_joltage = (tens * 10) + max_ones_digit;

                best_joltage = best_joltage.max(current_joltage);
            }

            best_joltage as u64
        })
        .sum()
}

fn part1_func(file_contents: &str) -> u64 {
    file_contents
        .lines()
        .filter(|line| !line.is_empty())
        .map(|bank| {
            let digits: Vec<u64> = bank
                .chars()
                .map(|c| c.to_digit(10).unwrap() as u64)
                .collect();

            digits
                .iter()
                .rev()
                .fold((0, 0), |(max_ones, best_jolt), &current_digit| {
                    let current_jolt = if max_ones > 0 {
                        current_digit * 10 + max_ones
                    } else {
                        0
                    };

                    (max_ones.max(current_digit), best_jolt.max(current_jolt))
                })
                .1
        })
        .sum::<u64>()
}

fn part2(file_contents: &str) -> u64 {
    const TARGET_LEN: usize = 12;

    file_contents
        .lines()
        .filter(|line| !line.is_empty())
        .map(|bank| {
            let digits: Vec<u64> = bank
                .chars()
                .map(|c| c.to_digit(10).unwrap() as u64)
                .collect();

            println!("digits = {:?}", digits);

            let (joltage, _) = (0..TARGET_LEN).fold((0, 0), |(current_joltage, start_idx), i| {
                let left = start_idx;
                let right = digits.len() - (TARGET_LEN - i) + 1;

                let slice = &digits[left..right];
                println!(
                    "current_slice = {:?}, left = {left}, right = {right}",
                    slice
                );

                // let (idx, max) = slice.iter().enumerate().max_by_key(|&(_, value)| value).unwrap();
                let (idx, max) = slice
                    .iter()
                    .enumerate()
                    .max_by(|(i1, v1), (i2, v2)| v1.cmp(v2).then(i2.cmp(i1)))
                    .unwrap();

                // let max = *slice.iter().max().unwrap();
                // let idx = slice.iter().position(|&v| v == max).unwrap();

                println!("current_joltage = {current_joltage}, max = {max}");

                (current_joltage * 10 + max, start_idx + idx + 1)
            });

            joltage
        })
        .sum()
}

fn main() {
    println!("Hello, world!");
}

#[cfg(test)]
mod tests {
    use super::*;

    const PART1_ANSWER_BASE: u64 = 357;
    const PART1_ANSWER_FULL: u64 = 17493;

    #[test]
    fn part1_base() {
        let contents = std::fs::read_to_string(format!("inputs/{DAY_STR}/base.txt")).unwrap();
        assert_eq!(part1(&contents), PART1_ANSWER_BASE);
    }

    #[test]
    fn part1_func_base() {
        let contents = std::fs::read_to_string(format!("inputs/{DAY_STR}/base.txt")).unwrap();
        assert_eq!(part1_func(&contents), PART1_ANSWER_BASE);
    }

    #[test]
    fn part1_full() {
        let contents = std::fs::read_to_string(format!("inputs/{DAY_STR}/full.txt")).unwrap();
        assert_eq!(part1(&contents), PART1_ANSWER_FULL);
    }

    #[test]
    fn part1_func_full() {
        let contents = std::fs::read_to_string(format!("inputs/{DAY_STR}/full.txt")).unwrap();
        assert_eq!(part1_func(&contents), PART1_ANSWER_FULL);
    }

    #[test]
    fn part2_base() {
        let contents = std::fs::read_to_string(format!("inputs/{DAY_STR}/base.txt")).unwrap();
        assert_eq!(part2(&contents), 3121910778619);
    }

    #[test]
    fn part2_full() {
        let contents = std::fs::read_to_string(format!("inputs/{DAY_STR}/full.txt")).unwrap();
        assert_eq!(part2(&contents), 173685428989126);
    }
}
