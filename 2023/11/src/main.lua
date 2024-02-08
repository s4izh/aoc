function file_exists(file)
    local f = io.open(file, "rb")
    if f then f:close() end
    return f ~= nil
end

-- get all lines from a file, returns an empty
-- list/table if the file does not exist
function lines_from(file)
    if not file_exists(file) then return {} end
    local lines = {}
    for line in io.lines(file) do
        lines[#lines + 1] = line
    end
    return lines
end

function copy_table(t)
    local new_table = {}
    for k, v in pairs(t) do
        new_table[k] = v
    end
    return new_table
end

-- print all line numbers and their contents
function duplicate_lines(lines)
    local new_lines = copy_table(lines)
    local to_duplicate = {}
    for i, line in pairs(lines) do
        local empty_line = true
        for j = 1, #line do
            local c = line:sub(j, j) -- line[j] doesn't work on a string
            if c ~= '.' then
                empty_line = false
                break
            end
        end
        if empty_line then
            to_duplicate[#to_duplicate + 1] = i
        end
    end
    for _, v in pairs(to_duplicate) do
        table.insert(new_lines, v, lines[v])
    end
    return new_lines
end

function duplicate_columns(lines)
    local new_lines = copy_table(lines)
    local appended = 0


    for j = 1, #lines[1] do
        local empty_column = true

        for i = 1, #lines do
            local c = lines[i]:sub(j, j)
            if c ~= '.' then
                empty_column = false
                break
            end
        end

        if empty_column then
            print('column', j, 'is empty')
            for i = 1, #lines do
                local pre_string = new_lines[i]:sub(1, j + appended - 1)
                local post_string = new_lines[i]:sub(j + appended, #lines[i])
                new_lines[i] = pre_string .. '.' .. post_string
                -- appended = appended + 1
            end
        end

        print('column', j, '---')

        for i, line in pairs(new_lines) do
            print('[' .. i .. ']', line)
        end
    end
    return new_lines
end

-- tests the functions above
local file = 'input/part1_input.txt'
local file_lines = lines_from(file)

local duplicated_lines = duplicate_lines(file_lines)

for i, line in pairs(duplicated_lines) do
    print('[' .. i .. ']', line)
end

local duplicated_columns = duplicate_columns(duplicated_lines)

-- for i, line in pairs(duplicated_columns) do
--   print('[' .. i .. ']', line)
-- end
