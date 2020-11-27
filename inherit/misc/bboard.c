// bboard.c

#include <ansi.h>

#define BOARD_CAPACITY query("capacity")

inherit ITEM;
inherit F_SAVE;

void setup()
{
	string loc;

	if (stringp(loc = query("location")))
		move(loc);
	set("no_get", 1);
	restore();
}

void init()
{
	add_action("do_post", "post");
	add_action("do_read", "read");
	add_action("do_discard", "discard");
}

string query_save_file()
{
	string id;

	if (! stringp(id = query("board_id"))) return 0;
	return DATA_DIR + "board/" + id;
}

string short()
{
	mapping *notes;
	int i, unread, last_read_time;

	notes = query("notes");
	if (! pointerp(notes) || ! sizeof(notes))
		return ::short() + " [ √ª”–»Œ∫Œ¡Ù—‘ ]";

	if (this_player())
        {
		last_read_time = (int)this_player()->query("board_last_read/" +
                                 (string)query("board_id"));
		for(unread = 0, i=sizeof(notes)-1; i>=0; i--, unread ++)
			if( notes[i]["time"] <= last_read_time ) break;
	}
	if (unread)
		return sprintf(HIC + "%s" + NOR + " [ %d ’≈¡Ù—‘£¨" + HIY + "%d" + NOR + " ’≈" +
                               HIR + "Œ¥∂¡" + NOR + "]", ::short(), sizeof(notes), unread);
	else
		return sprintf("%s [ %d ’≈¡Ù—‘ ]", ::short(), sizeof(notes));
}

string long()
{
	mapping *notes;
	int i, last_time_read;
	string msg, myid;
        object where;

        where = environment(this_player());

        if ((string)file_name(where) == "/d/wizard/noname_room"
            && !wizardp(this_player()))
                return "∏√¡Ù—‘∞Ê÷ª”–Œ◊ ¶≤≈ƒ‹≤È‘ƒ°£\n";  

	notes = query("notes");
	msg = query("long");
	msg = msg + "¡Ù—‘∞Êµƒ π”√∑Ω∑®«Îº˚ help board°£\n";
	if (! pointerp(notes) || ! sizeof(notes)) return query("long");

	last_time_read = this_player()->query("board_last_read/" + (string)query("board_id"));
        i = sizeof(notes) - 50;
        if (i < 0) i = 0;
	for (; i < sizeof(notes); i++)
		msg += sprintf("%s[%2d]" NOR "  %-40s %12s (%s)\n",
			(notes[i]["time"] > last_time_read ? HIY: ""),
			i + 1, notes[i]["title"], notes[i]["author"], ctime(notes[i]["time"])[0..15]);
	return msg;
}

// This is the callback function to process the string returned from the
// editor defined in F_EDIT of player object.
void done_post(object me, mapping note, int n, string text)
{
        int i;
        int t;
        int pl;
        string sign;
        string pure;
	mapping *notes;

        if (! n) n = me->query("env/default_sign");
        if (! stringp(sign = me->query(sprintf("env/sign%d", n))))
        {
                // auto select the first none null sign
                for (i = 1; i <= 4; i++)
                {
                        sign = me->query(sprintf("env/sign%d", i));
                        if (stringp(sign)) break;
                }
        }

        if (stringp(sign))
        {
                sign = replace_string(sign, "\\n", "\n");
                sign = trans_color(sign, 1);
                pure = filter_color(sign);
                if (strlen(pure) >= 1 &&
		    pure[strlen(pure) - 1] != '\n')
			sign += "\n";

                pure = filter_color(text);
                pl = strlen(pure);
                if (pl >= 1 && pure[pl - 1] != '\n')
                        text += "\n\n" + sign;
                else
                if (pl >= 2 && pure[pl - 2] != '\n')
                        text += "\n" + sign;
                else
                        text += sign;
        }

	note["msg"] = text;
	notes = query("notes");
	if (! pointerp(notes) || ! sizeof(notes))
		notes = ({ note });
	else
        {
                i = sizeof(notes) - 1;
                if (note["time"] <= notes[i]["time"])
                        note["time"] = notes[i]["time"] + 1;
		notes += ({ note });
        }

	// Truncate the notes if maximum capacity exceeded.
        if( sizeof(notes) > BOARD_CAPACITY )
                notes = notes[BOARD_CAPACITY / 2 .. BOARD_CAPACITY];
        if(sizeof(text)>=3000){//’‚∏ˆ ˝◊÷ «≤‚ ‘≥ˆ¿¥µƒ°£∫«∫« by xgchen
            tell_object(me,"”…”⁄ƒ„µƒ¡Ù—‘Ã´≥§¡À°£œµÕ≥Ω´ ”Œ™µ∑¬“Œﬁ∑®¥¶¿Ì°£\n");
           return ;
        }
	set("notes", notes);
	tell_object(me, "¡Ù—‘ÕÍ±œ°£\n");

	save();
	return;
}

int do_post(string arg, int n)
{
	mapping note;
	if (! arg) return notify_fail("¡Ù—‘«Î÷∏∂®“ª∏ˆ±ÍÃ‚°£\n");
 if((time()-(int)this_player()->query("postover")) < 60)
            return notify_fail("ƒ„“—æ≠‘⁄≤ªæ√¡Ù—‘¡À£¨«Î…‘µ»1∑÷÷”‘Ÿ≥¢ ‘°£\n");
        if (sscanf(arg, "%s with %d", arg, n) != 2)
                n = 0;

        if (replace_string(arg, " ", "") == "")
                arg = "Œﬁ±ÍÃ‚";
	
	note = allocate_mapping(4);
	note["title"] = arg;
	  if(sizeof(arg)>=40){//’‚∏ˆ ˝◊÷ «≤‚ ‘≥ˆ¿¥µƒ°£∫«∫«by xgchen
            return notify_fail("ƒ„µƒ¡Ù—‘±ÍÃ‚Ã´≥§¡À£¨œµÕ≥¥¶¿Ì≤ª¡À°£\n");
        }
        note["author"] = this_player()->query("name") + "-" + this_player()->query("id");
	note["time"] = time();
	this_player()->set("postover",time());
	this_player()->edit((: done_post, this_player(), note, n :));
	return 1;
}

int do_read(string arg)
{
	int num;
	mapping *notes, last_read_time;
	string myid;
        object where;

        where = environment(this_player());

        if ((string)file_name(where) == "/d/wizard/noname_room"
            && !wizardp(this_player()))
                return notify_fail("∏√¡Ù—‘∞Ê÷ª”–Œ◊ ¶≤≈ƒ‹≤È‘ƒ°£\n");        

	last_read_time = this_player()->query("board_last_read");
	myid = query("board_id");
	notes = query("notes");

	if (! pointerp(notes) || ! sizeof(notes))
		return notify_fail("¡Ù—‘∞Â…œƒø«∞√ª”–»Œ∫Œ¡Ù—‘°£\n");

	if (! arg) return notify_fail("÷∏¡Ó∏Ò Ω£∫read <¡Ù—‘±‡∫≈>|new|next\n");
	if (arg == "new" || arg == "next")
        {
		if (! mapp(last_read_time) || undefinedp(last_read_time[myid]))
			num = 1;
		else
			for (num = 1; num<=sizeof(notes); num++)
				if (notes[num-1]["time"] > last_read_time[myid])
                                        break;
			
	} else
        if (! sscanf(arg, "%d", num))
		return notify_fail("ƒ„“™∂¡µ⁄º∏’≈¡Ù—‘£ø\n");

	if (num < 1 || num > sizeof(notes))
		return notify_fail("√ª”–’‚’≈¡Ù—‘°£\n");
	num--;

          
          
          
this_player()->start_more(sprintf(
"[36m----------------------------------------------------------------------
[47;34m ±Í Ã‚ [44;37m %-62s
[47;34m ◊˜ ’ﬂ [44;37m %-19s   ®q®T®T®T®T®T®T®T®T®T®T®T®T®T®T®T®T®T®T®r
[47;34m ∆™  ˝ [44;37m %-11d           ®U"HIR"«ÎŒƒ√˜ π”√£¨∑Ò‘Ú"HIY"ƒ„"HIR"ªÚ"HIY"Ã˚◊”"HIR"ø…ƒ‹ª·±ª…æ≥˝"NOR"[44;37m®U
[47;34m  ± º‰ [44;37m %-12s          ®t®T®T®T®T®T®T®T®T®T®T®T®T®T®T®T®T®T®T®s
[m[36m----------------------------------------------------------------------\n\n[m",
                     notes[num]["title"], notes[num]["author"], num + 1, ctime(notes[num]["time"])[0..9]) 
                     + notes[num]["msg"]); 
       this_player()->start_more( sprintf
("[36m\n----------------------------------------------------------------------
[36m|                                                "HIY"÷–ª™”¢–€ª∂”≠ƒ˙£°"NOR"[36m    |"NOR"
[36m----------------------------------------------------------------------\n",));   
	// Keep track which post we were reading last time.
	if (! mapp(last_read_time))
		this_player()->set("board_last_read", ([ myid: notes[num]["time"] ]));
	else 
		if (undefinedp(last_read_time[myid]) || notes[num]["time"] > last_read_time[myid])
			last_read_time[myid] = notes[num]["time"];

	return 1;
}


int do_discard(string arg)
{
	mapping *notes;
	int num;

	if (! arg || sscanf(arg, "%d", num) != 1)
		return notify_fail("÷∏¡Ó∏Ò Ω£∫discard <¡Ù—‘±‡∫≈>\n");
	notes = query("notes");
	if (! arrayp(notes) || num < 1 || num > sizeof(notes))
		return notify_fail("√ª”–’‚’≈¡Ù—‘°£\n");
	num--;
	if (notes[num]["author"] != (string) this_player()->query("name") + "-" +
                                    this_player()->query("id")
	&&	(string)SECURITY_D->get_status(this_player()) != "(admin)") 
	//&&      (string)SECURITY_D->get_status(this_player()) != "(arch)")
		return notify_fail("’‚∏ˆ¡Ù—‘≤ª «ƒ„–¥µƒ°£\n");

	notes = notes[0..num-1] + notes[num+1..sizeof(notes)-1];
	set("notes", notes);
	this_player()->delete("postover");
	save();
	write("…æ≥˝µ⁄ " + (num+1) + " ∫≈¡Ù—‘....Ok°£\n");
	return 1;
}
