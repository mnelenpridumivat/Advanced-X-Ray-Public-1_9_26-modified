#include "stdafx.h"
#include "script_export_space.h"

/*xr_vector<script_exporter_base*> script_exporter_container;
std::mutex script_exporter_mutex;

void script_exporter_add(script_exporter_base* new_value)
{
	std::lock_guard<std::mutex> guard(script_exporter_mutex);
	script_exporter_container.push_back(new_value);
}*/

xr_unordered_map<script_exporter_key_base*, script_exporter_data>& get_script_export_container()
{
	static xr_unordered_map<script_exporter_key_base*, script_exporter_data> script_exporter_container;
	return script_exporter_container;
}
