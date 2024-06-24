#include "C_Drawable.h"

C_Drawable::C_Drawable() : sortOrder(0), layer(DrawLayer::Default) { }

void C_Drawable::SetOrder(size_t order) { sortOrder = order; }
size_t C_Drawable::GetSortOrder() const { return sortOrder; }
void C_Drawable::SetDrawLayer(DrawLayer drawLayer) { layer = drawLayer; }
DrawLayer C_Drawable::GetDrawLayer() const { return layer; }
