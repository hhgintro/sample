--drop procedure sp_city_select
alter procedure sp_city_select
@i_id int,
@i_name varchar(10),
@o_id int output,
@o_name varchar(10) output
as
begin

select * from city where id = @i_id;
select * from city where id = @i_id+1;
select * from city where id = @i_id+2;

select @i_id + 100 as o_id, @i_name as o_char;

set @o_id = @i_id + len(@i_name) * 100;
set @o_name = 'out_' + @i_name;
return 0;
end

/*

create table city(id int, name varchar(10))


insert into city values (1,'111');
insert into city values (2,'222');
insert into city values (3,'333');
insert into city values (4,'444');
insert into city values (5,'555');
insert into city values (6,'666');
insert into city values (7,'777');
insert into city values (8,'888');
insert into city values (9,'999');
insert into city values (10,'aaa');
insert into city values (11,'°¡°¡°¡');

declare @out int,@o_id int,@o_name varchar(10)
 exec @out = sp_city_select 9,'hhg', @o_id output, @o_name output;
select @out as result, @o_id as o_id, @o_name as o_name

*/

