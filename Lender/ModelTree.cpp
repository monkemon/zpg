#include "ModelTree.h"
#include "tree.h"

ModelTree::ModelTree(LightModel* lm, glm::vec3 color)
	: Renderable(lm, color)
{
	this->loadModel(tree, 556884, 3, 2);
}
