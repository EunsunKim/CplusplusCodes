
// This class is part of a class in the Scenen Controller.hpp

namespace Graphics  {
      template <RenderSystem RS>
      class SceneController : public iSceneController {
         private:
         protected:
         public:
            ActorManager<RS> actMan;
            CameraManager<RS> camMan;
            LightManager<RS> lgtMan;
            NodeManager<RS> nodMan;
            
            iActor* createActor(){ 
					    return actMan.createObject();
				    }

            iCamera* createCamera() { 
					    return camMan.createObject();
				    }

            iLight* createLight() { 
					    return lgtMan.createObject();
				    }
            iNode* createNode() { 
              return Emperor::NodeManager::getPtr()->createObject(); 
            }
       };
