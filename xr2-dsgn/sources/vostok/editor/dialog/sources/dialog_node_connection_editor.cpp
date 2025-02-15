////////////////////////////////////////////////////////////////////////////
//	Created		: 18.12.2009
//	Author		: Sergey Prishchepa
//	Copyright (C) GSC Game World - 2009
////////////////////////////////////////////////////////////////////////////
#include "pch.h"
#include "dialog_node_connection_editor.h"
#include "dialog_document.h"

using vostok::dialog_editor::dialog_node_connection_editor;
using vostok::dialog_editor::dialog_document;
using vostok::editor::controls::hypergraph::node;

void dialog_node_connection_editor::execute(node^ source, node^ destination)
{
	m_document->add_connection(source, destination);
}
