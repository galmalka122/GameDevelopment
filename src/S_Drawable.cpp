#include "S_Drawable.h"

void S_Drawable::Add(std::vector<std::shared_ptr<Object>> &objects) {
    for (auto object : objects) { Add(object); }
    Sort();
}

void S_Drawable::ProcessRemovals() {

    auto it = drawables.begin();
    while(it != drawables.end()){

        auto object = *it;

        if(object->IsQueuedForRemoval()){
            it = drawables.erase(it);
        } else {
            ++it;
        }
    }
}

void S_Drawable::Draw(Window &window) {
    for(auto& drawable : drawables){ drawable->Draw(window); }
}

void S_Drawable::Add(std::shared_ptr<Object> object) {

    std::shared_ptr<C_Drawable> drawable = object->GetDrawable();

    if(drawable != nullptr){ drawables.emplace_back(object); }
}

void S_Drawable::Sort() {

    std::sort(drawables.begin(), drawables.end(), [](std::shared_ptr<Object> a, std::shared_ptr<Object> b) -> bool {
        return a->GetDrawable()->GetSortOrder() < b->GetDrawable()->GetSortOrder();
    });
}
